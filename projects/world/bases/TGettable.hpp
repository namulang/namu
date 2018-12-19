#pragma once

#include "TGettable.inl"

namespace wrd
{
#define TEMPL template <typename T, typename S>
#define THIS TGettable<T, S>

    WRD_CLASS_DEFINE(TEMPL, THIS)

	TEMPL T& THIS::get() { return _get().cast<T>(); }
	TEMPL const T& THIS::get() const { return _get().cast<const T>(); }

#undef TEMPL
#undef THIS

#define TEMPL template <typename T>
#define THIS TGettable<T, void>
	
	TEMPL T& THIS::get() { return _get().cast<T>(); }
	TEMPL const T& THIS::get() const { return _get().cast<const T>(); }

#undef TEMPL
#undef THIS
}
