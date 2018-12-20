#pragma once

#include "TGettable.inl"

namespace wrd
{
#define TEMPL template <typename T, typename S>
#define THIS TGettable<T WRD_COMMA() S>

    WRD_CLASS_DEFINE_2(TEMPL, TGettable<T WRD_COMMA() S>)
    TEMPL const T* WRD_EVAL(THIS)::operator->() const { return &get(); }
    TEMPL T* WRD_EVAL(THIS)::operator->() { return &get(); }
    TEMPL const T* WRD_EVAL(THIS):operator*() const { return &get(); }
    TEMPL T* WRD_EVAL(THIS)::operator*() { return &get(); }
	TEMPL T& WRD_EVAL(THIS)::get() { return _get().cast<T>(); }
	TEMPL const T& WRD_EVAL(THIS)::get() const { return _get().cast<const T>(); }

#undef TEMPL
#undef THIS

#define TEMPL template <typename T>
#define THIS TGettable<T, void>

    TEMPL const T* THIS::operator->() const { return &get(); }
    TEMPL T* THIS::operator->() { return &get(); }
    TEMPL const T* THIS:operator*() const { return &get(); }
    TEMPL T* THIS::operator*() { return &get(); }
	TEMPL T& THIS::get() { return _get().cast<T>(); }
	TEMPL const T& THIS::get() const { return _get().cast<const T>(); }

#undef TEMPL
#undef THIS
}
