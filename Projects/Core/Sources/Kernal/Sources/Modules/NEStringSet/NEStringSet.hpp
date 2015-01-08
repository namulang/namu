#pragma once
#include "../NEString/NEString.hpp"

namespace NE
{
	template
	class NE_DLL NEArrayTemplate<NEString, true, NEString, NEType::NESTRING_SET>;
	class NE_DLL NEStringSet : public NEArrayTemplate<NEString, true, NEString, NEType::NESTRING_SET>
	{
	public:
		typedef NEStringSet ThisClass;
		typedef NEArrayTemplate<NEString, true, NEString, NEType::NESTRING_SET> SuperClass;

		NEStringSet() : SuperClass() {}
		NEStringSet(type_count size) : SuperClass() {}
	};
}