#pragma once
#include "../NEString/NEString.hpp"

namespace NE
{
	template
	class NE_DLL NETVector<NEString>;
	class NE_DLL NEStringSet : public NETVector<NEString>
	{
		NE_DECLARE_CLASS(NEStringSet, NETVector<NEString>)

	public:
		NEStringSet() : Super() {}
		NEStringSet(type_count size) : Super() {}
	};
}