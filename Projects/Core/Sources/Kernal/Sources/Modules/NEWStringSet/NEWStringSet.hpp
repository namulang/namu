#pragma once

#include "../NEWString/NEWString.hpp"

namespace NE
{
	template
	class NE_DLL NETArray<NEWString, false, NEWString>;
	class NE_DLL NEWStringSet : public NETArray<NEWString, false, NEWString> 
	{
		typedef NETArray<NEWString, false, NEWString> _Super;
		NE_DECLARE_CLASS(NEWStringSet, _Super)

	public:
		NEWStringSet() : Super() {}
		NEWStringSet(type_count size) : Super() {}
	};
}