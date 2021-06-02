#pragma once

#include "ncontainer.hpp"
#include "../../../ast/node.hpp"
#include "iterator/titerator.inl"

namespace wrd {

    class nchain : public ncontainer {
        WRD_CLASS(nchain, ncontainer)

        friend class elemIteration;
        class elemIteration : public iteration {
            WRD_CLASS(elemIteration, iteration)
            friend class nchain;

        public:
            elemIteration(const nchain& own, const nchain& iteratingChain, const iterator& conIter)
                : _own(const_cast<nchain&>(own)), _ownIter(iteratingChain), _iter(conIter) {
                    if(!_iter) next(1);
                }

            wbool isEnd() const override {
                return !_iter;
            }

            wcnt next(wcnt step) override {
                if(step <= 0) return 0;
                wcnt stepped = _iter.next(step),
                     remain = step - stepped;
                if(remain == 0) return stepped;

                // arr iteration has reached to tail of the arr:
                _ownIter = _ownIter->_next;
                if(!_ownIter) return stepped;
                _iter = _ownIter->_arr->begin();
                remain--;
                return stepped + next(remain);
            }

            node& get() override {
                return *_iter;
            }

            ncontainer& getContainer() override { return _own; }
            iterator& getContainerIter() { return _iter; }

        protected:
            wbool _onSame(const typeProvidable& rhs) const override {
                if(!super::_onSame(rhs)) return false;

                const me& cast = (const me&) rhs;
                if(nul(cast)) return false;

                return _iter == cast._iter;
            }

        private:
            nchain& _own;
            tstr<nchain> _ownIter;
            iterator _iter;
        };

    public:
        nchain();
        explicit nchain(const ncontainer& con): _arr(con) {}

        wcnt len() const override;

        using super::set;
        wbool set(const iterator& at, const node& new1) override;

        using super::add;
        wbool add(const iterator& at, const node& new1) override;
        wbool add(const node& new1) override;

        using super::del;
        wbool del(const node& it) override;
        wbool del() override;
        wbool del(const iterator& at) override;
        wcnt del(const iterator& from, const iterator& end) override;

        tstr<me> link(const ncontainer& new1);
        wbool link(const me& new1);
        wbool unlink();

        void empty() override;

        ncontainer& getContainer() { return *_arr; }
        const ncontainer& getContainer() const { return *_arr; }
        me& getNext() { return *_next; }
        const me& getNext() const { return *_next; }

        using super::each;
        template <typename E>
        void each(const iterator& from, const iterator& end, std::function<wbool(me&, E&)> l) {
            const me* endChn = nullptr;
            if(!nul(end)) {
                endChn = &end.getContainer().cast<me>();
                if(nul(endChn)) return;
            }

            for(me* e = (me*) &from.getContainer().cast<me>();
                !nul(e) && e != endChn;
                e = &(*e->_next)) {
                auto& arr = e->_arr->template cast<E>();
                if(nul(arr)) continue;

                if(!l(*e, arr)) break;
            }
        }
        /// @param  end Nullable. meaning of the end of nchain list.
        template <typename E>
        void each(const iterator& from, const iterator& end, std::function<wbool(const me&, const E&)> l) const {
            const me* endChn = nullptr;
            if(!nul(end)) {
                endChn = &end.getContainer().cast<me>();
                if(nul(endChn)) return;
            }

            for(const me* e = &from.getContainer().cast<me>();
                !nul(e) && e != endChn;
                e = &(*e->_next)) {
                auto& arr = e->_arr->template cast<E>();
                if(nul(arr)) continue;

                if(!l(*e, arr)) break;
            }
        }
        template <typename E>
        void each(std::function<wbool(me&, E&)> l) {
            each(begin(), nulOf<iterator>(), l);
        }
        template <typename E>
        void each(std::function<wbool(const me&, const E&)> l) const {
            each(begin(), nulOf<iterator>(), l);
        }

        /// returned deep cloned of this object.
        /// @remark even if the chain has already linked to the another chain instance,
        ///         only this object will be deep cloned. cloned instance has the same linkage like
        ///         which the original chain object has.
        tstr<instance> deepClone() const override {
            me* ret = new me(getContainer().deepClone()->template cast<ncontainer>());
            ret->link(getNext());
            return tstr<instance>(ret);
        }

    protected:
        iteration* _onMakeIteration(wcnt step) const override {
            me* unconst = const_cast<me*>(this);
            iteration* ret = new elemIteration(*unconst, *unconst, _arr->begin());
            ret->next(step);
            return ret;
        }

    private:
        iterator& _getContainerIterFromChainIter(const iterator& wrap) {
            if(nul(wrap)) return nulOf<iterator>();
            if(!wrap._step->getType().isSub<elemIteration>()) return nulOf<iterator>();
            elemIteration& cast = (elemIteration&) *wrap._step;
            if(nul(cast)) return nulOf<iterator>();

            return cast.getContainerIter();
        }
        me& _getLastChain();
        const me& _getLastChain() const WRD_UNCONST_FUNC(_getLastChain())

    private:
        tstr<ncontainer> _arr;
        tstr<me> _next;
    };
}
