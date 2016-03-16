#pragma once

#include "../NETSuperClassChecker/NETSuperClassChecker.hpp"
#include "../NEUnknown/NEUnknown.hpp"

namespace NE
{
	template <typename T, type_bool IS_SUPERCLASS_DEFINED = NETSuperClassChecker<T>::IS_SUPERCLASS_DEFINED>
	class NETSuperClassDeterminder : public NETypeChecker
	{
	public:
		typedef typename T::Super Super;
	};
	template <typename T>
	class NETSuperClassDeterminder<T, false>
	{
	public:
		typedef NEUnknown Super;
	};
}