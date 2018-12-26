#pragma once

#include "TChain.inl"

namespace wrd
{
#define THIS TChain<T>
#define TEMPL template <typename T>

	WRD_CLASS_DEFINE(THIS)

#undef TEMPL
#undef THIS
}

