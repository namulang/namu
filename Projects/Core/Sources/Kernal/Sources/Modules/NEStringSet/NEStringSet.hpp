#pragma once
#include "../NEString/NEString.hpp"

namespace NE
{
	template
	class NE_DLL NETArray<NEString, false, NEString, NEType::NESTRING_SET>;
	class NE_DLL NEStringSet : public NETArray<NEString, false, NEString, NEType::NESTRING_SET>
	{
	public:
		typedef NEStringSet ThisClass;
		typedef NETArray<NEString, false, NEString, NEType::NESTRING_SET> SuperClass;

		NEStringSet() : SuperClass() {}
		NEStringSet(type_count size) : SuperClass() {}
	};
}