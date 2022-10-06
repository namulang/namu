#pragma once

#include "tmarshaling.hpp"

namespace namu {

#define TEMPL template <typename T>
#define ME tmarshaling<tarr<T>, true>

    TEMPL
    tarr<T> ME::toNative(node& it) {
        return tarr<T>(it.cast<arr>());
    }

    TEMPL
    template <typename E>
    str ME::toMgd(E* it) {
        return new arr(*it);
    }

    TEMPL
    typename ME::mgdType& ME::onAddParam() {
        return *new mgdType();
    }

    TEMPL
    typename ME::mgdType& ME::onGetRet() {
        return *new mgdType();
    }

#undef ME
#undef TEMPL

}
