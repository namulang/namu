#pragma once

#include "../../ast/param.hpp"

namespace wrd {

    class node;
    template <typename K, typename V>
    class tnbicontainer;
    template <typename T, typename TACTIC> class tnarr;
    typedef tnarr<node, strTactic> narr;

    /// @remark tbicontainable has API treating iter ref and element as its parameter.
    template <typename K, typename V>
    class tbicontainable {
        WRD_DECL_ME(tbicontainable)

    public:
        #include "iter/biter.hpp"

    public:
        virtual ~tbicontainable() {}

        // operator:
        V& operator[](const K& key) { return get(key); }
        const V& operator[](const K& key) const { return get(key); }

        // len:
        virtual wcnt len() const = 0;

        // has:
        virtual wbool has(const K& key) const = 0;

        // get:
        virtual V& get(const K& key) = 0;
        const V& get(const K& key) const WRD_UNCONST_FUNC(get(key))
        template <typename V1> V1& get(const K& key) { return get(key).template cast<V1>(); }
        template <typename V1> const V1& get(const K& key) const WRD_UNCONST_FUNC(get<V1>(key))
        template <typename V1>
        V1& get(std::function<wbool(const K&, const V1&)> l) const;
        V& get(std::function<wbool(const K&, const V&)> l) const;
        template <typename V1>
        tnarr<V1, strTactic> getAll(std::function<wbool(const K&, const V1&)> l) const;
        narr getAll(std::function<wbool(const K&, const V&)> l) const;

        // iter:
        iter begin() const { return iterate(0); }
        virtual iter end() const { return iterate(len()); }
        virtual iter last() const { return iterate(len()-1); }
        iter iterate(wcnt step) const { return iter(_onMakeIteration(step)); }

        // set:
        virtual wbool set(const K& key, const V& new1) = 0;
        wbool set(const K& key, const V* new1) { return set(key, *new1); }

        // add:
        virtual wbool add(const K& key, const V& val) = 0;
        wbool add(const K& key, const V* val) { return add(key, *val); }
        wcnt add(const iter& from, const iter& to) {
            int ret = 0;
            for(iter e=from; e != to ;++e)
                if(add(e.getKey(), e.getVal()))
                    ret++;
            return ret;
        }
        wcnt add(const tbicontainable& rhs) { return add(rhs.begin(), rhs.end()); }

        // del:
        /// delete last element if exists.
        virtual wbool del(const K& it) = 0;
        virtual wcnt del(const iter& from, const iter& end) = 0;
        wcnt del(const tbicontainable& rhs) { return del(rhs.begin(), rhs.end()); }

        // etc:
        virtual void rel() = 0;

        virtual tstr<instance> deepClone() const = 0;

    protected:
        virtual iteration* _onMakeIteration(wcnt step) const = 0;
    };

    typedef tbicontainable<std::string, node> bicontainable;
}
