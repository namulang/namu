#pragma once

#include "TGettable.inl"
#include "../bases/Instance.hpp"
#include "../metas/TClass.inl"

namespace wrd
{
#define TEMPL template <typename T, typename S>
#define THIS TGettable<T WRD_COMMA() S>

    WRD_CLASS_DEFINE_2(TEMPL, TGettable<T WRD_COMMA() S>)
    TEMPL const T* WRD_UNWRAP(THIS)::operator->() const { return &get(); }
    TEMPL T* WRD_UNWRAP(THIS)::operator->() { return &get(); }
    TEMPL const T* WRD_UNWRAP(THIS)::operator*() const { return &get(); }
    TEMPL T* WRD_UNWRAP(THIS)::operator*() { return &get(); }
	TEMPL T& WRD_UNWRAP(THIS)::get() { return this->_get().template cast<T>(); }

	TEMPL const T& WRD_UNWRAP(THIS)::get() const
	{
		WRD_UNCONST_2(THIS, unconst)
		return unconst->_get().template cast<const T>(); 
	}

#undef TEMPL
#undef THIS

#define TEMPL template <typename T>
#define THIS TGettable<T, void>

    TEMPL const T* THIS::operator->() const { return &get(); }
    TEMPL T* THIS::operator->() { return &get(); }
    TEMPL const T* THIS::operator*() const { return &get(); }
    TEMPL T* THIS::operator*() { return &get(); }
	TEMPL T& THIS::get() { return _get().template cast<T>(); }

	TEMPL const T& THIS::get() const
	{
		WRD_UNCONST_2(THIS, unconst)
		return unconst->_get().template cast<const T>();
	}

#undef TEMPL
#undef THIS
}
