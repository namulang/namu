#pragma once
#include "../NEString/NEString.hpp"

namespace NE
{
	template
	class NE_DLL NETVector<NEString, false, NEString>;
	class NE_DLL NEStringSet : public NETVector<NEString, false, NEString>
	{
		typedef NETVector<NEString, false, NEString> _Super;
		NE_DECLARE_CLASS(NEStringSet, _Super)

	public:
		NEStringSet() : Super() {}
		NEStringSet(type_count size) : Super() {}
	};
}