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
                return !_ownIter || !_iter;
            }

            wcnt next(wcnt step) override {
                wcnt remain = step;

                // if _ownIter was invalidated then _iter too.
                while(remain > 0) {
                    remain -= _iter.next(remain);
                    if(remain <= 0) break;

                    // _iter moved to 'End' state now.
                    _ownIter = _ownIter->_next;
                    if(!_ownIter) break;
                    _iter = _ownIter->_arr->begin();
                    if(_iter) remain--;
                }

                return step - remain;
            }

            ncontainer& getContainer() override { return _ownIter->template cast<ncontainer>(); }
            const ncontainer& getContainer() const WRD_UNCONST_FUNC(getContainer())

            instance& get() override {
                return *_iter;
            }

            wrd::iter& getContainerIter() { return _iter; }

        protected:
            wbool _onSame(const typeProvidable& rhs) const override {
                const me& cast = (const me&) rhs;
                return  (isEnd() && cast.isEnd()) ||
                        _iter == cast._iter;
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
                return  (isEnd() && trg.isEnd()) ||
                        _chn == trg._chn;
            }

        private:
            tstr<tnchain> _chn;
        };

        typedef titer<me> chnIter;

    public:
        tnchain();
        template <typename E>
        explicit tnchain(const tnarr<E>& arr): _arr(arr) {}
        template <typename E>
        explicit tnchain(const tnarr<E>* arr): _arr(arr) {}

        // len:
        wcnt len() const override;
        wcnt chainLen() const;

        // iter:
        chnIter beginChain() const { return iterChain(0); }
        chnIter endChain() const {
            return chnIter(new chnIteration());
        }
        chnIter lastChain() const {
            me* last = nullptr;
            for(chnIter e=beginChain(); e ; ++e)
                last = &e.get();

            return chnIter(new chnIteration(*last));
        }
        chnIter iterChain(wcnt step) const {
            chnIter ret = _iterChain(*this);
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
            me* ret = wrap(getContainer().deepClone()->template cast<ncontainer>());
            ret->link(getNext());
            return tstr<instance>(ret);
        }

        /// wrap given container as the same level to this chain.
        /// @param toShallowWrap
        ///        if this is a chain, then the wrap func returns it as it is.
        ///        if this is any container except chain, then it returns after
        ///        wrapping given container.
        template <typename E>
        static tnchain<E>* wrap(const ncontainer& toShallowWrap) {
            typedef tnchain<E> O;

            O* ret = const_cast<O*>(&toShallowWrap.cast<O>());
            if(!ret) {
                ret = new O();
                ret->_arr.bind(toShallowWrap);
            }

            return ret;
        }

        template <typename E>
        static tnchain<E>* wrap(const ncontainer* toShallowWrap) {
            return wrap<E>(*toShallowWrap);
        }

        static me* wrap(const ncontainer& toShallowWrap) {
            return wrap<T>(toShallowWrap);
        }

        static me* wrap(const ncontainer* toShallowWrap) {
            return wrap<T>(*toShallowWrap);
        }

        /// wrap given container no matter what it is.
        template <typename E>
        static tnchain<E>* wrapDeep(const ncontainer& toDeepWrap) {
            tnchain<E>* innerChn = wrap(toDeepWrap);

            tnchain<E>* ret = new tnchain<E>();
            ret->_arr.bind(innerChn);
            return ret;
        }

        template <typename E>
        static tnchain<E>* wrapDeep(const ncontainer* toDeepWrap) {
            return wrapDeep(*toDeepWrap);
        }

        static me* wrapDeep(const ncontainer& toDeepWrap) {
            return wrap<T>(toDeepWrap);
        }

        static me* wrapDeep(const ncontainer* toDeepWrap) {
            return wrap<T>(*toDeepWrap);
        }

    protected:
        iteration* _onMakeIteration(wcnt step) const override {
            // TODO: optimize using containerIteration
            me* unconst = const_cast<me*>(this);
            iteration* ret = new elemIteration(*unconst, _arr->begin());
            ret->next(step);
            return ret;
        }

        chnIter _iterChain(const me& start) const {
            return chnIter(new chnIteration(start));
        }

    private:
        wrd::iter& _getArrIterFromChainIter(const wrd::iter& wrapper) {
            if(nul(wrapper)) return nulOf<wrd::iter>();
            if(!wrapper._step->getType().isSub<elemIteration>()) return nulOf<wrd::iter>();
            elemIteration& cast = (elemIteration&) *wrapper._step;
            if(nul(cast)) return nulOf<wrd::iter>();

            return cast.getContainerIter();
        }

    private:
        tstr<ncontainer> _arr;
        tstr<me> _next;
    };

    typedef tnchain<node> nchain;
}
