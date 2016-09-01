#pragma once
#include "../NEString/NEString.hpp"

namespace NE
{
	template
	class NE_DLL NETArray<NEString, false, NEString>;
	class NE_DLL NEStringSet : public NETArray<NEString, false, NEString>
	{
		typedef NETArray<NEString, false, NEString> _Super;
		NE_DECLARE_CLASS(NEStringSet, _Super)

	public:
		NEStringSet() : Super() {}
		NEStringSet(type_count size) : Super() {}
	};
}