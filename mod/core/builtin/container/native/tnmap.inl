#pragma once

#include "tnmap.hpp"
#include "../../../ast/node.hpp"
#include "tnbicontainer.inl"

namespace namu {

#define TEMPL template <typename K, typename V, typename TACTIC>
#define ME tnmap<K, V, TACTIC>

    TEMPL
    wbool ME::has(const K& key) const {
        return _map.find(key) != _map.end();
    }

    TEMPL
    V& ME::get(const K& key) {
        if(!has(key)) return nulOf<V>();

        return *_map.lower_bound(key)->second;
    }

    TEMPL
    void ME::_getAll(const K& key, narr& tray) const {
        auto end = _map.upper_bound(key);
        for(auto e=_map.lower_bound(key); e != end ;++e)
            tray.add(*e->second);
    }

    TEMPL
    wbool ME::add(const K& key, const V& new1) {

        _map.insert({key, wrap(new1)});
        return true;
    }

    TEMPL
    wbool ME::del(const K& it) {
        _map.erase(it);
        return true;
    }

    TEMPL
    wbool ME::del(const iter& at) {
        if(!at.isFrom(*this)) return WRD_W("from is not an iterator of this container."), false;
        if(at.isEnd()) return WRD_W("at is end of the container. skip function."), false;

        _map.erase(_getIterationFrom(at)._citer);
        return true;
    }

    TEMPL
    wbool ME::del(const iter& from, const iter& end) {
        if(!from.isFrom(*this) || !end.isFrom(*this))
            return WRD_W("from or end is not an iterator of this container"), false;

        _map.erase(_getIterationFrom(from)._citer, _getIterationFrom(end)._citer);
        return true;
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
