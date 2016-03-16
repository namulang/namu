#pragma once

#include "../NEWString/NEWString.hpp"

namespace NE
{
	template
	class NE_DLL NETArray<NEWString, false, NEWString>;
	class NE_DLL NEWStringSet : public NETArray<NEWString, false, NEWString> 
	{
	public:
		typedef NEWStringSet ThisClass;
		typedef NETArray<NEWString, false, NEWString> SuperClass;

		NEWStringSet() : SuperClass() {}
		NEWStringSet(type_count size) : SuperClass() {}
	};
}