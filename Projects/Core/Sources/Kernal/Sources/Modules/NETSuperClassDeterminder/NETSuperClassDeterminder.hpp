#pragma once

#include "../NETSuperClassChecker/NETSuperClassChecker.hpp"
#include "../NEUnknown/NEUnknown.hpp"

namespace NE
{
	template <typename T, type_bool IS_SUPERCLASS_DEFINED = NETSuperClassChecker<T>::IS_SUPERCLASS_DEFINED>
	class NETSuperClassDeterminder : public NETypeChecker
	{
		typedef NETSuperClassDeterminder<T, IS_SUPERCLASS_DEFINED> _This;
		NE_DECLARE_INTERFACE(_This, NETypeChecker)

	public:
		typedef typename T::Super Super;
	};
	template <typename T>
	class NETSuperClassDeterminder<T, false> : public NETypeChecker
	{
		typedef NETSuperClassDeterminder<T, false> _This;
		NE_DECLARE_INTERFACE(_This, NETypeChecker)

	public:
		typedef NEUnknown Super;
	};
}