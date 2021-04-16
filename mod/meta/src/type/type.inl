#pragma once

#include "ttype.hpp"
#include "type.hpp"

namespace wrd {

#define ME type

    template <typename T>
    wbool ME::isSuper() const {
        return isSuper(ttype<T>::get());
    }

    template <typename T>
    wbool ME::isSub() const {
        return ttype<T>::get().isSuper(*this);
    }

#undef ME
}
