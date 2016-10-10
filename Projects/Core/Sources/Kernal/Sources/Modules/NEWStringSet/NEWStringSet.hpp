#pragma once

#include "../NEWString/NEWString.hpp"

namespace NE
{
	template
	class NE_DLL NETVector<NEWString>;
	class NE_DLL NEWStringSet : public NETVector<NEWString> 
	{
		typedef NETVector<NEWString, false, NEWString> _Super;
		NE_DECLARE_CLASS(NEWStringSet, _Super)

	public:
		NEWStringSet() : Super() {}
		NEWStringSet(type_count size) : Super() {}
	};
}