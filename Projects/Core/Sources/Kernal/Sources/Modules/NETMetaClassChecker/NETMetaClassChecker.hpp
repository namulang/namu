#pragma once

#include "../NETypeChecker/NETypeChecker.hpp"

namespace NE
{
	template <typename T>
	class NETMetaClassChecker : public NETypeChecker
	{
	private:
		template <typename T>
		static yes _isMetaClassDefined(typename T::MetaClass*);
		template <typename T>
		static no _isMetaClassDefined(...);

	public:
		static const type_bool IS_METACLASS_DEFINED = sizeof(_isMetaClassDefined<T>(0)) == sizeof(yes);
	};
}