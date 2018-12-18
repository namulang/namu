#pragma once

#include "TBindable.inl"

namespace wrd
{
#define TEMPL template <typename T>
#define THIS TBindable<T>

	WRD_CLASS_DEFINE(THIS)
	TEMPL const T* THIS::operator->() const { return &get(); }
	TEMPL T* THIS::operator->() { return &get(); }
	TEMPL const T* THIS::operator*() const { return &get(); }
	TEMPL T* THIS::operator*() { return &get(); }

#undef TEMPL
#undef THIS
}
