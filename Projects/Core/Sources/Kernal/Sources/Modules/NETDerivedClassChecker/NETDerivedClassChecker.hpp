#pragma once

#include "../NETypeChecker/NETypeChecker.hpp"

namespace NE
{
	template <typename Derived, typename Parent>
	class NETDerivedClassChecker : public NETypeChecker
	{
	private:
		static yes _isDerivedOf(Parent*);
		static no _isDerivedOf(...);

	public:
		static const type_bool IS_DERIVED_OF = sizeof(_isDerivedOf((Derived*)0)) == sizeof(yes);
	};
}