#pragma once

#include "WType.hpp"
#include "../ast/TRef.hpp"

namespace wrd {

#define THIS WType

    template <typename T>
    wbool THIS::isImpli() const {
        return isImpli(TType<T>::get());
    }

    template <typename T>
    TRef<T> THIS::asImpli(const Node& it) const {
        return asImpli(it, TType<T>::get());
    }

    template <typename T>
    wbool THIS::is() const {
        return is(TType<T>::get());
    }

    template <typename T>
    TRef<T> THIS::as(const Node& it) const {
        return as(it, TType<T>::get());
    }

#undef THIS
}
