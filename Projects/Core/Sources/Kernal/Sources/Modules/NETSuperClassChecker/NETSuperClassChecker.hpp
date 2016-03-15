#pragma once

#include "../NETypeChecker/NETypeChecker.hpp"

namespace NE
{
	template <typename T>
	class NETSuperClassChecker : public NETypeChecker
	{
	private:
		template <typename T>
		static yes _isSuperClassChecker(typename T::SuperClass*);
		template <typename T>
		static no _isSuperClassChecker(...);

	public:
		static const type_bool IS_SUPERCLASS_DEFINED = sizeof(_isSuperClassChecker<T>(0)) == sizeof(yes);
	};
}