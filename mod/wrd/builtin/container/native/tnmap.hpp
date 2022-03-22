#pragma once

#include "tnbicontainer.hpp"
#include "../../../ast/node.hpp"

namespace wrd {

    template <typename K, typename V, typename TACTIC = strTactic>
    class tnmap : public tnbicontainer<K, V> {
        typedef tnbicontainer<K, V> __super;
        WRD(CLASS(tnmap, __super))
        template <typename K, typename V> friend class tmap;
        typedef tstr<V, TACTIC> wrap;
        typedef std::map<K, wrap> cmap;
        typedef cmap::iterator citer;
        typedef std::pair<K, V> cpair;
        typedef typename super::iter iter;

    public:
        friend class nmapIteration;
#include "../iter/nmapIteration.hpp"

    public:
        tnmap() {}

        // operator:
        V& operator[](const K& key) override { return get(key); }
        const V& operator[](const K& key) const override { return get(key); }

        // len:
        wcnt len() const override;

        // has:
        wbool has(const K& key) const override;

        // get:
        using super::get;
        V& get(const K& key) override;
        const V& get(const K& key) const override WRD_UNCONST_FUNC(get(key))

        // set:
        using super::set;
        wbool set(const K& at, const V& new1) override;

        // add:
        using super::add;
        wbool add(const K& key, const V& new1) override;

        // del:
        using super::del;
        wbool del(const K& it) override;
        wcnt del(const iter& from, const iter& end) override;

        // etc:
        void rel() override;

        tstr<instance> deepClone() const override;

    protected:
        iteration* _onMakeIteration(wcnt step) const override {
            me* unconst = const_cast<me*>(this);
            iteration* ret = new nmapIteration(*unconst, unconst->_map.begin());
            ret->next(step);
            return ret;
        }

    private:
        nmapIteration& _getIterationFrom(const iter& it) {
            if(nul(it)) return nulOf<nmapIteration>();
            if(!it.isFrom(*this)) return nulOf<nmapIteration>();
            return (nmapIteration&) *it._step;
        }

    private:
        cmap _map;
    };

    typedef tnmap<node, str> narr;
    typedef tnmap<node, tstr<node, refTactic> scope;
}
