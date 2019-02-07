#pragma once

#include "Thing.inl"
#include "../memory/TStrong.hpp"

namespace wrd
{
#define THIS Thing
	template <typename T> Strong THIS::to() { return to(T::getClassStatic()); }
	template <typename T> CStrong THIS::to() const { return to(T::getClassStatic()); }
#undef THIS
}
