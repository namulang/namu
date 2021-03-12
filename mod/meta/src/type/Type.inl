#pragma once

#include "TType.hpp"
#include "Type.hpp"

namespace wrd {

#define THIS Type

    template <typename T>
    wbool THIS::isSuper() const {
        return isSuper(TType<T>::get());
    }

    template <typename T>
    wbool THIS::isSub() const {
        return TType<T>::get().isSuper(*this);
    }

#undef THIS
}
