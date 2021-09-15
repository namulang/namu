#pragma once

#include "wtype.hpp"
#include "../ast/tref.hpp"

namespace wrd {

#define ME wtype

    template <typename T>
    wbool ME::isImpli() const {
        return isImpli(ttype<T>::get());
    }

    template <typename T>
    tref<T> ME::asImpli(const node& it) const {
        return asImpli(it, ttype<T>::get());
    }

    template <typename T>
    wbool ME::is() const {
        return is(ttype<T>::get());
    }

    template <typename T>
    tref<T> ME::as(const node& it) const {
        return as(it, ttype<T>::get());
    }

#undef ME
}
