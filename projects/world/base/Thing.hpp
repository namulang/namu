#pragma once

#include "Thing.inl"
#include "../memory/TStrong.hpp"

namespace wrd
{
#define THIS Thing
	template <typename T> Strong THIS::to() { return to(T::getClassStatic()); }
	template <typename T> CStrong THIS::to() const { return to(T::getClassStatic()); }
	template <typename T> T& THIS::down() { return (T&) _down(T::getClassStatic()); }
	//	구체클래스로 캐스트한다. dynamic_cast와 동급이다.
	//	invisible이다.
	template <typename T> const T& THIS::down() const
	{
		WRD_UNCONST()
		return unconst.down<T>();
	}
	template <typename T> wbool THIS::isSuper() const { return getClass().isSuperCls(T::getClassStatic()); }
	template <typename T> wbool THIS::isSub() const { return T::getClassStatic().isSuperCls(getClass()); }
#undef THIS
}
