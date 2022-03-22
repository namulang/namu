#pragma once

#include "tnucontainer.hpp"
#include "../../../ast/node.hpp"

namespace wrd {

    class node;

    template <typename T, typename defaultContainer = narr>
    class tnchain : public tnucontainer<T> {
        WRD(CLASS(tnchain, tnucontainer<T>))
        typedef typename super::iter iter;
        typedef typename super::iteration iteration;

    public:
        friend class elemIteration;
#include "../iter/nchainIteration.hpp"

    public:
        tnchain();
        template <typename E>
        explicit tnchain(const tnarr<E>& arr): _arr(arr) {}
        template <typename E>
        explicit tnchain(const tnarr<E>* arr): _arr(arr) {}

        // len:
        wcnt len() const override;
        wcnt chainLen() const;

        // set:
        using super::set;
        wbool set(const iter& at, const node& new1) override;

        // add:
        using super::add;
        wbool add(const iter& at, const node& new1) override;

        // link:
        tstr<me> link(const tnucontainer<T>& new1);
        wbool link(const me& new1);
        wbool unlink();

        // del:
        using super::del;
        wbool del(const iter& at) override;
        wcnt del(const iter& from, const iter& end) override;

        // etc:
        void rel() override;

        tnucontainer<T>& getContainer();
        const tnucontainer<T>& getContainer() const { return *_arr; }

        me& getNext() { return *_next; }
        const me& getNext() const { return *_next; }

        /// returned deep cloned of this object.
        /// @remark even if the chain has already linked to the another chain instance,
        ///         only this object will be deep cloned. cloned instance has the same linkage like
        ///         which the original chain object has.
        tstr<instance> deepClone() const override {
            me* ret = wrap(getContainer().deepClone()->template cast<tnucontainer<T>>());
            ret->link(getNext());
            return tstr<instance>(ret);
        }

        /// wrap given container as the same level to this chain.
        /// @param toShallowWrap
        ///        if this is a chain, then the wrap func returns it as it is.
        ///        if this is any container except chain, then it returns after
        ///        wrapping given container.
        static me* wrap(const tnucontainer<T>& toShallowWrap);
        static me* wrap(const tnucontainer<T>* toShallowWrap) {
            return wrap(*toShallowWrap);
        }

        /// wrap given container no matter what it is.
        static me* wrapDeep(const tnucontainer<T>& toDeepWrap) {
            me* innerChn = wrap(toDeepWrap);

            me* ret = new me();
            ret->_arr.bind(innerChn);
            return ret;
        }

        static me* wrapDeep(const tnucontainer<T>* toDeepWrap) {
            return wrapDeep(*toDeepWrap);
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
        iter& _getArrIterFromChainIter(const iter& wrapper) {
            if(nul(wrapper)) return nulOf<iter>();
            if(!wrapper._step->getType().template isSub<elemIteration>()) return nulOf<iter>();
            elemIteration& cast = (elemIteration&) *wrapper._step;
            if(nul(cast)) return nulOf<iter>();

            return cast._iter;
        }

    private:
        tstr<tnucontainer<T>> _arr;
        tstr<me> _next;
    };

    typedef tnchain<node> nchain;
}
