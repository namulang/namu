#pragma once

#include "TGettable.inl"

namespace wrd
{
#define TEMPL template <typename T, typename S>
#define THIS decltype(TGettable<T, S>) // wrap decltype() because compiler regards it has 2 args.

    WRD_CLASS_DEFINE(TEMPL, WRD_FUNNEL(THIS))

	TEMPL T& THIS::get() { return _get().cast<T>(); }
	TEMPL const T& THIS::get() const { return _get().cast<const T>(); }

#undef TEMPL
#undef THIS

#define TEMPL template <typename T>
#define THIS decltype(TGettable<T, void>)
	
	TEMPL T& THIS::get() { return _get().cast<T>(); }
	TEMPL const T& THIS::get() const { return _get().cast<const T>(); }

#undef TEMPL
#undef THIS
}
