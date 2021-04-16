#pragma once

#include "WType.hpp"
#include "../ast/TRef.hpp"

namespace wrd {

#define ME WType

    template <typename T>
    wbool ME::isImpli() const {
        return isImpli(TType<T>::get());
    }

    template <typename T>
    TRef<T> ME::asImpli(const Node& it) const {
        return asImpli(it, TType<T>::get());
    }

    template <typename T>
    wbool ME::is() const {
        return is(TType<T>::get());
    }

    template <typename T>
    TRef<T> ME::as(const Node& it) const {
        return as(it, TType<T>::get());
    }

#undef ME
}
