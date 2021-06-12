#pragma once

#include "ncontainer.hpp"
#include "../../../ast/node.hpp"
#include "iter/titer.inl"

namespace wrd {

    class node;

    template <typename T>
    class tnchain : public ncontainer {
        WRD_CLASS(tnchain, ncontainer)

        friend class elemIteration;
        class elemIteration : public iteration {
            WRD_CLASS(elemIteration, iteration)
            friend class tnchain;

        public:
            elemIteration(const tnchain& iteratingChain, const wrd::iter& conIter)
                : _ownIter(iteratingChain), _iter(conIter) {
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

            ncontainer& getContainer() override {
                return _iter->cast<ncontainer>();
            }

            instance& get() override {
                return *_iter;
            }

            wrd::iter& getContainerIter() { return _iter; }

        protected:
            wbool _onSame(const typeProvidable& rhs) const override {
                if(!super::_onSame(rhs)) return false;

                const me& cast = (const me&) rhs;
                if(nul(cast)) return false;

                return _iter == cast._iter;
            }

        private:
            tstr<tnchain> _ownIter;
            wrd::iter _iter;
        };

        friend class chnIteration;
        class chnIteration : public iteration {
            WRD_CLASS(chnIteration, iteration)
            friend class tnchain;

        public:
            chnIteration(const tnchain& start): _chn(start) {}
            chnIteration() {}

            wbool isEnd() const override {
                return !_chn;
            }

            wcnt next(wcnt step) override {
                wcnt n=0;
                for(; n < step ;n++) {
                    if(isEnd()) return n;

                    _chn.bind(_chn->getNext());
                }

                return n;
            }

            instance& get() override {
                return *_chn;
            }

            ncontainer& getContainer() override {
                return *_chn;
            }

        protected:
            wbool _onSame(const typeProvidable& rhs) const override {
                if(!super::_onSame(rhs)) return false;

                const me& trg = (const me&) rhs;
                return _chn == trg._chn;
            }

        private:
            tstr<tnchain> _chn;
        };

        typedef titer<me> chnIter;

    public:
        tnchain();
        explicit tnchain(const ncontainer& con): _arr(con) {}

        // len:
        wcnt len() const override;

        // iter:
        chnIter beginChain() const { return iterChain(0); }
        chnIter endChain() const {
            return chnIter(new chnIteration());
        }
        titer<me> lastChain() const {
            me* last = nullptr;
            for(chnIter e=beginChain(); e ; ++e)
                last = &e.get();

            return chnIter(new chnIteration(*last));
        }
        titer<me> iterChain(wcnt step) const {
            titer<me> ret(new chnIteration(*this));
            ret.next(step);
            return ret;
        }

        // set:
        using super::set;
        wbool set(const wrd::iter& at, const node& new1) override;

        // add:
        using super::add;
        wbool add(const wrd::iter& at, const node& new1) override;

        // link:
        tstr<me> link(const ncontainer& new1);
        wbool link(const me& new1);
        wbool unlink();

        // del:
        using super::del;
        wbool del(const wrd::iter& at) override;
        wcnt del(const wrd::iter& from, const wrd::iter& end) override;

        // etc:
        void empty() override;

        ncontainer& getContainer() { return *_arr; }
        const ncontainer& getContainer() const { return *_arr; }

        me& getNext() { return *_next; }
        const me& getNext() const { return *_next; }

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
            // TODO: optimize using containerIteration
            me* unconst = const_cast<me*>(this);
            iteration* ret = new elemIteration(*unconst, _arr->begin());
            ret->next(step);
            return ret;
        }

    private:
        wrd::iter& _getContainerIterFromChainIter(const wrd::iter& wrap) {
            if(nul(wrap)) return nulOf<wrd::iter>();
            if(!wrap._step->getType().isSub<elemIteration>()) return nulOf<wrd::iter>();
            elemIteration& cast = (elemIteration&) *wrap._step;
            if(nul(cast)) return nulOf<wrd::iter>();

            return cast.getContainerIter();
        }

    private:
        tstr<ncontainer> _arr;
        tstr<me> _next;
    };

    typedef tnchain<node> nchain;
}
