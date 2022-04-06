#pragma once

#include "tnmap.hpp"
#include "../../../ast/node.hpp"
#include "tnbicontainer.inl"

namespace wrd {

#define TEMPL template <typename K, typename V, typename TACTIC>
#define ME tnmap<K, V, TACTIC>

    TEMPL
    wbool ME::has(const K& key) const {
        return _map.find(key) != _map.end();
    }

    TEMPL
    V& ME::get(const K& key) {
        if(!has(key)) return nulOf<V>();

        return _map[key].get();
    }

    TEMPL
    wbool ME::set(const K& at, const V& new1) {
        if(!has(at))
            return false;

        _map[at].bind(new1);
        return true;
    }

    TEMPL
    wbool ME::add(const K& key, const V& new1) {
        if(nul(key) || nul(new1)) return false;

        _map.insert({key, wrap(new1)});
        return true;
    }

    TEMPL
    wbool ME::del(const K& it) {
        return _map.erase(it) > 0;
    }

    TEMPL
    wcnt ME::del(const iter& from, const iter& end) {
        if(!from.isFrom(this) || end.isFrom(this))
            return WRD_W("from or end is not an iterator of this container"), 0;

        wcnt ret = 0;
        for(iter e=from; e ;++e)
            ret += del(e.getKey());
        return ret;
    }

    TEMPL
    wcnt ME::len() const {
        return _map.size();
    };

    TEMPL
    void ME::rel() {
        _map.clear();
    }

    TEMPL
    tstr<instance> ME::deepClone() const {
        me* ret = new me();
        for(iter e=this->begin(); e ;++e)
            ret->add(e.getKey(), (V*) e.getVal().clone());

        return tstr<instance>(ret);
    }

#undef TEMPL
#undef ME
}
