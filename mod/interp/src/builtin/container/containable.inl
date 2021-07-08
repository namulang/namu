#pragma once

#include "containable.hpp"
#include "../../ast/node.hpp"
#include "native/tnarr.inl"

namespace wrd {

#define ME containable

    template <typename T>
    T& ME::get(std::function<wbool(const T&)> l) const {
        for(titer<T> e=begin<T>(); e ; ++e) {
            const T& elem = *e;
            if(l(elem))
                return const_cast<T&>(elem);
        }

        return nulOf<T>();
    }

    template <typename T>
    tnarr<T> ME::getAll(std::function<wbool(const T&)> l) const {
        tnarr<T> ret;
        for(titer<T> e=begin<T>(); e ; ++e) {
            const T& elem = *e;
            if(l(elem))
                ret.add(elem);
        }

        return ret;
    }

#undef ME
}
