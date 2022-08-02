#pragma once

#include "tucontainable.hpp"
#include "tbicontainable.hpp"
#include "iter/uiter.inl"
#include "../../ast/node.hpp"
#include "native/tnarr.inl"

namespace namu {

#define TEMPL template <typename T>
#define ME tucontainable<T>

    TEMPL
    template <typename E>
    E& ME::get(std::function<wbool(const E&)> l) const {
        for(const T& elem : *this) {
            const E& cast = elem.template cast<E>();
            if(!nul(cast) && l(cast)) // elem should be typeProvidable.
                return (E&) cast;
        }

        return nulOf<E>();
    }

    TEMPL
    template <typename E>
    tnarr<E> ME::getAll(std::function<wbool(const E&)> l) const {
        tnarr<E> ret;
        for(const T& elem : *this) {
            const E& cast = elem.template cast<E>();
            if(!nul(cast) && l(cast))
                ret.add(cast);
        }

        return ret;
    }

    TEMPL
    template <typename K, typename V>
    wcnt ME::add(const tbicontainable<K, V>& rhs) {
        static_assert(areBaseOfT<T, V>::value, "given type 'V' is not subtype of 'T'");
        wcnt ret = 0;
        for(auto e=rhs.begin(); e ;++e)
            ret += add(*e);
        return ret;
    }

    TEMPL
    T& ME::get(std::function<wbool(const T&)> l) const {
        return this->get<T>(l);
    }

    TEMPL
    narr ME::getAll(std::function<wbool(const T&)> l) const {
        return this->getAll<T>(l);
    }

#undef ME
#undef TEMPL
}
