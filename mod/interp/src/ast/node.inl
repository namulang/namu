#pragma once

#include "node.hpp"
#include "tref.hpp"

namespace wrd {

#define ME node

    template <typename T>
    tref<T> ME::asImpli() const {
        return tref<T>(asImpli(ttype<T>::get()));
    }

    template <typename T>
    tref<T> ME::as() const {
        return tref<T>(as(ttype<T>::get()));
    }

#undef ME
}
