#pragma once

#include "tbindable.hpp"

namespace wrd {

#define TEMPL template <typename T>
#define ME tbindable<T>

    TEMPL ME::operator wbool() const { return isBind(); }

    TEMPL wbool ME::canBind(const T& it) const {
        if(nul(it)) return false;
        return canBind(it.getType());
    }

#undef ME
#undef TEMPL
}
