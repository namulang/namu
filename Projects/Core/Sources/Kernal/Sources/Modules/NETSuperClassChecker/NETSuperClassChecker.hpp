#pragma once

#include "../NETypeChecker/NETypeChecker.hpp"

namespace NE
{
	template <typename T>
	class NETSuperClassChecker : public NETypeChecker
	{
	private:
		static yes _isSuperClassChecker(typename T::Super*);
		static no _isSuperClassChecker(...);

	public:
		static const type_bool IS_SUPERCLASS_DEFINED = sizeof(_isSuperClassChecker((T*)0)) == sizeof(yes);
	};
}