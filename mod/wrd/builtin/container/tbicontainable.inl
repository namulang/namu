#pragma once

#include "tbicontainable.hpp"
#include "iter/biter.inl"
#include "../../ast/node.hpp"
#include "native/tnarr.inl"

namespace wrd {

#define TEMPL template <typename K, typename V>
#define ME tbicontainable<K, V>

    TEMPL
    template <typename V1>
    V1& ME::get(std::function<wbool(const K&, const V1&)> l) const {
        for(const std::pair<K, V>& p : this) {
            if(p.second.isSub<V1>() && l(p.first, (V1&) p.second)) // elem should be typeProvidable.
                return (V1&) p.second;
        }

        return nulOf<V1>();
    }

    TEMPL
    template <typename V1>
    tnarr<V1> ME::getAll(std::function<wbool(const K&, const V1&)> l) const {
        tnarr<V1> ret;
        for(const std::pair<K, V>& p : this)
            if(p.second.isSub<V1>() && l(p.first, (V1&) p.second))
                ret.add(elem);

        return ret;
    }

#undef ME
#undef TEMPL
}
