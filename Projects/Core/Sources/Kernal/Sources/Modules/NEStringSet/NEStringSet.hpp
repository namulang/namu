#pragma once
#include "../NEString/NEString.hpp"

namespace NE
{
	template
	class NE_DLL NETArray<NEString, false, NEString>;
	class NE_DLL NEStringSet : public NETArray<NEString, false, NEString>
	{
	public:
		typedef NEStringSet ThisClass;
		typedef NETArray<NEString, false, NEString> SuperClass;

		NEStringSet() : SuperClass() {}
		NEStringSet(type_count size) : SuperClass() {}
	};
}