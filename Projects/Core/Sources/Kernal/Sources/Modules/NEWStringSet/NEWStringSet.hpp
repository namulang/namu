#pragma once

#include "../NEWString/NEWString.hpp"

namespace NE
{
	template
	class NE_DLL NEArrayTemplate<NEWString, false, NEWString, NEType::NEWSTRING_SET>;
	class NE_DLL NEWStringSet : public NEArrayTemplate<NEWString, false, NEWString, NEType::NEWSTRING_SET> 
	{
	public:
		typedef NEWStringSet ThisClass;
		typedef NEArrayTemplate<NEWString, false, NEWString, NEType::NEWSTRING_SET> SuperClass;

		NEWStringSet() : SuperClass() {}
		NEWStringSet(type_count size) : SuperClass() {}
	};
}