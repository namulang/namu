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
    E& ME::get(std::function<wbool(const E&)> l) const {
        for(const T& elem : this) {
            if(elem.template isSub<E>() && l(elem)) // elem should be typeProvidable.
                return const_cast<E&>(elem);
        }

        return nulOf<E>();
    }

    TEMPL
    template <typename E>
    tnarr<E> ME::getAll(std::function<wbool(const E&)> l) const {
        tnarr<E> ret;
        for(const T& elem : this)
            if(elem.template isSub<E>() && l(elem))
                ret.add(elem);

        return ret;
    }

#undef ME
#undef TEMPL
}
