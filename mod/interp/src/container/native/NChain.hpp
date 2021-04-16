#pragma once

#include "NContainer.hpp"
#include "../../ast/Node.hpp"

namespace wrd {

    class NChain : public NContainer {
        WRD_CLASS(NChain, NContainer)

        friend class NChainIteration;
        class NChainIteration : public Iteration {
            WRD_CLASS(NChainIteration, Iteration)
            friend class NChain;

        public:
            NChainIteration(const NChain& own, const NChain& iteratingChain, const Iter& conIter)
                : _own(const_cast<NChain&>(own)), _ownIter(iteratingChain), _iter(conIter) {
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
                _iter = _ownIter->_arr->head();
                remain--;
                return stepped + next(remain);
            }

            Node& get() override {
                return *_iter;
            }

            NContainer& getContainer() override { return _own; }
            Iter& getContainerIter() { return _iter; }

        protected:
            wbool _onSame(const TypeProvidable& rhs) const override {
                if(!super::_onSame(rhs)) return false;

                const me& cast = (const me&) rhs;
                if(nul(cast)) return false;

                return _iter == cast._iter;
            }

        private:
            NChain& _own;
            TStr<NChain> _ownIter;
            Iter _iter;
        };

    public:
        NChain();
        explicit NChain(const NContainer& con): _arr(con) {}

        wcnt getLen() const override;

        using super::set;
        wbool set(const Iter& at, const Node& new1) override;

        Iter head() const override;
        Iter tail() const override;
        Iter last() const override;
        Iter iter(wcnt step) const override;

        using super::add;
        wbool add(const Iter& at, const Node& new1) override;
        wbool add(const Node& new1) override;

        using super::del;
        wbool del() override;
        wbool del(const Node& it) override;
        wbool del(const Iter& at) override;
        wcnt del(const Iter& from, const Iter& end) override;

        TStr<NChain> link(const NContainer& new1);
        wbool link(const NChain& new1);
        wbool unlink();

        void empty() override;

        NContainer& getContainer() { return *_arr; }
        const NContainer& getContainer() const { return *_arr; }
        NChain& getNext() { return *_next; }
        const NChain& getNext() const { return *_next; }

        using super::each;
        template <typename T>
        void each(const Iter& from, const Iter& end, std::function<wbool(NChain&, T&)> l) {
            const NChain* endChn = nullptr;
            if(!nul(end)) {
                endChn = &end.getContainer().cast<NChain>();
                if(nul(endChn)) return;
            }

            for(NChain* e = (NChain*) &from.getContainer().cast<NChain>();
                !nul(e) && e != endChn;
                e = &(*e->_next)) {
                auto& arr = e->_arr->cast<T>();
                if(nul(arr)) continue;

                if(!l(*e, arr)) break;
            }
        }
        /// @param  end Nullable. meaning of the end of NChain list.
        template <typename T>
        void each(const Iter& from, const Iter& end, std::function<wbool(const NChain&, const T&)> l) const {
            const NChain* endChn = nullptr;
            if(!nul(end)) {
                endChn = &end.getContainer().cast<NChain>();
                if(nul(endChn)) return;
            }

            for(const NChain* e = &from.getContainer().cast<NChain>();
                !nul(e) && e != endChn;
                e = &(*e->_next)) {
                auto& arr = e->_arr->cast<T>();
                if(nul(arr)) continue;

                if(!l(*e, arr)) break;
            }
        }
        template <typename T>
        void each(std::function<wbool(NChain&, T&)> l) {
            each(head(), nulOf<Iter>(), l);
        }
        template <typename T>
        void each(std::function<wbool(const NChain&, const T&)> l) const {
            each(head(), nulOf<Iter>(), l);
        }

    private:
        Iter& _getContainerIterFromChainIter(const Iter& wrap) {
            if(nul(wrap)) return nulOf<Iter>();
            if(!wrap._step->getType().isSub<NChainIteration>()) return nulOf<Iter>();
            NChainIteration& cast = (NChainIteration&) *wrap._step;
            if(nul(cast)) return nulOf<Iter>();

            return cast.getContainerIter();
        }
        NChain& _getLastChain();
        const NChain& _getLastChain() const WRD_UNCONST_FUNC(_getLastChain())

        TStr<NContainer> _arr;
        TStr<NChain> _next;
    };
}
