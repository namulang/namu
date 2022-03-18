#pragma once

#include "tucontainable.hpp"
#include "iter/uiter.inl"
#include "../../ast/node.hpp"
#include "native/tnarr.inl"

namespace wrd {

#define TEMPL template <typename T>
#define ME tucontainable<T>

    TEMPL
    template <typename E>
    E& ME::get(std::function<wbool(const T&)> l) const {
        for(const T& elem : this) {
            if(elem.isSub<T>() && l(elem)) // elem should be typeProvidable.
                return const_cast<T&>(elem);
        }

        return nulOf<T>();
    }

    TEMPL
    template <typename T>
    tnarr<T> ME::getAll(std::function<wbool(const T&)> l) const {
        tnarr<T> ret;
        for(const T& elem : this)
            if(elem.isSub<T>() && l(elem))
                ret.add(elem);

        return ret;
    }

#undef ME
#undef TEMPL
}
