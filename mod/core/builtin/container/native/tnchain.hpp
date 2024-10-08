#pragma once

#include "tnmap.hpp"

namespace nm {

    class node;

    template <typename K, typename V, typename _defaultContainer = tnmap<K, V>>
    class tnchain: public tnbicontainer<K, V> {
        typedef tnbicontainer<K, V> _super_;
        typedef tnchain<K, V, _defaultContainer> _me_;
        NM(CLASS(_me_, _super_))

    public:
        typedef typename super::iter iter;
        typedef typename super::iteration iteration;
        friend class chainIteration;
        typedef _defaultContainer defaultContainer;
#include "../iter/nchainIteration.hpp"

    public:
        tnchain(): _map(new defaultContainer()) {}

        explicit tnchain(const super& arr): _map(arr) {}

        explicit tnchain(const super& org, const me& next): _map(org), _next(next) {}

        explicit tnchain(const std::initializer_list<std::pair<K, V*>>& elems) {
            for(const auto& e: elems)
                _map->add(e.first, *e.second);
        }

    public:
        // has:
        using super::in;
        nbool in(const K& key) const override;

        // len:
        ncnt len() const override;
        ncnt chainLen() const;

        using super::get;
        V& get(const K& key) override;

        // add:
        using super::add;
        nbool add(const K& key, const V& val) override;

        // link:
        tstr<me> link(const super& new1);
        virtual nbool link(const me& new1);
        nbool unlink();

        // del:
        using super::del;
        nbool del(const K& at) override;
        nbool del(const iter& at) override;
        nbool del(const iter& from, const iter& end) override;

        // etc:
        void rel() override;

        super& getContainer();

        const super& getContainer() const { return *_map; }

        me& getNext() { return *_next; }

        const me& getNext() const { return *_next; }

        /// return most not null next element of this chain.
        me& getTail();
        const me& getTail() const NM_CONST_FUNC(getTail())

        /// returned deep cloned of this instance with all chained ones.
        /// @remark when the chain has already linked to the another chain instance,
        ///         not only this object, but also all of chained instances will be deep cloned.
        void onCloneDeep(const clonable& from) override;

        /// wrap given container as the same level to this chain.
        /// @param toShallowWrap
        ///        if this is a chain, then the wrap func returns it as it is.
        ///        if this is any container except chain, then it returns after
        ///        wrapping given container.
        template <typename T> static T* wrap(const super& toShallowWrap);

        /// mock this chain and let it chain another container differ to original.
        /// this func keep accessing next element to chain it.
        /// @param until the loop will be terminated when next element has same address to this.
        ///        chain you assigned to 'until' will be cloned to.
        me* cloneChain(const super& until) const;
        me* cloneChain(const me& until) const;

        /// mock all of this chain until 'next' is null.
        me* cloneChain() const { return cloneChain(nulOf<me>()); }

    protected:
        iteration* _onMakeIteration(ncnt step) const override {
            // TODO: optimize using containerIteration
            me* unconst = const_cast<me*>(this);
            iteration* ret = new chainIteration(*unconst, _map->begin());
            ret->next(step);
            return ret;
        }

        iteration* _onMakeIteration(const K& key) const override {
            me* unconst = const_cast<me*>(this);
            return new chainIteration(*unconst, _map->iterate(key), key);
        }

        void _getAll(const K& key, narr& tray) const override;

    private:
        iter& _getMapIterFromChainIter(const iter& wrapper) {
            if(!wrapper._step->getType().template isSub<chainIteration>()) return nulOf<iter>();
            chainIteration& cast = (chainIteration&) *wrapper._step orNul(iter);

            return cast._iter;
        }

    private:
        tstr<super> _map;
        tstr<me> _next;
    };
} // namespace nm
