#pragma once

#include "Node.hpp"
#include "TRef.hpp"

namespace wrd {

#define THIS Node

    template <typename T>
    TRef<T> THIS::asImpli() const {
        return TRef<T>(asImpli(TType<T>::get()));
    }

    template <typename T>
    TRef<T> THIS::as() const {
        return TRef<T>(as(TType<T>::get()));
    }

#undef THIS
}
