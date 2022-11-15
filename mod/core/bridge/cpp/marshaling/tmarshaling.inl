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
    typename ME::mgd& ME::onAddParam() {
        return *new mgd();
    }

    TEMPL
    typename ME::mgd& ME::onGetRet() {
        return *new mgd();
    }

#undef ME
#undef TEMPL

}
