#pragma once

#include "Node.hpp"
#include "TRef.hpp"

namespace wrd {

#define ME Node

    template <typename T>
    TRef<T> ME::asImpli() const {
        return TRef<T>(asImpli(TType<T>::get()));
    }

    template <typename T>
    TRef<T> ME::as() const {
        return TRef<T>(as(TType<T>::get()));
    }

#undef ME
}
