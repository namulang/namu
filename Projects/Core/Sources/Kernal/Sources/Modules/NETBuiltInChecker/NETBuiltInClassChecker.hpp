#pragma once

#include "../NETypeChecker/NETypeChecker.hpp"

namespace NE
{
	template <typename T>
	class NETBuiltInClassChecker : public NETypeChecker
	{
	private:
		static yes _isBuiltInClass(NEObject*);
		static no _isBuiltInClass(...);

	public:
		static const type_bool IS_BUILT_IN_CLASS = sizeof(_isBuiltInClass((T*)0)) == sizeof(yes);
	};
}