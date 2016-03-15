#pragma once

#include "../NETSuperClassChecker/NETSuperClassChecker.hpp"

namespace NE
{
	template <typename T, type_bool IS_SUPERCLASS_DEFINED = NETSuperClassChecker<T>::IS_SUPERCLASS_DEFINED>
	class NETSuperClassDeterminder : public NETypeChecker
	{
	public:
		typedef typename T::MetaClass MetaClass;
	};
	template <typename T>
	class NETSuperClassDeterminder<T, false>
	{
	public:
		typedef NEUnknown MetaClass;
	};
}