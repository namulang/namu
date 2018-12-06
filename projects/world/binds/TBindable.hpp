#pragma once

#include "TBindable.inl"

namespace wrd
{
#define THIS TBindable<T>
#define TEMPLATE template <typename T>

    TEMPLATE const T* THIS::operator->() const { return &get(); }
    TEMPLATE T* THIS::operator->() const { return &get(); }
    TEMPLATE const T* THIS::operator*() const { return &get(); }
    TEMPLATE T* THIS::operator*() { return &get(); }
    TEMPLATE T& THIS::get() { return _get().cast<T>(); }
    TEMPLATE const T& THIS::get() const { return _get().cast<const T>(); }

#undef THIS
#undef TEMPLATE
}
