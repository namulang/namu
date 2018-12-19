#pragma once

#pragma message "4-2-2-2-1"
#include "TBindable.inl"
#pragma message "4-2-2-2-2"

namespace wrd
{
#define TEMPL template <typename T, typename S>
#define THIS TBindable<T, S>

    WRD_CLASS_DEFINE_2(TEMPL, THIS)
    TEMPL const T* THIS::operator->() const { return &get(); }
    TEMPL T* THIS::operator->() { return &get(); }
    TEMPL const T* THIS::operator*() const { return &get(); }
    TEMPL T* THIS::operator*() { return &get(); }

#undef TEMPL
#undef THIS

#define TEMPL template <typename T>
#define THIS TBindable<T, void>

    TEMPL const T* THIS::operator->() const { return &get(); }
    TEMPL T* THIS::operator->() { return &get(); }
    TEMPL const T* THIS::operator*() const { return &get(); }
    TEMPL T* THIS::operator*() { return &get(); }

#undef TEMPL
#undef THIS
}
#pragma message "4-2-2-2-3"
