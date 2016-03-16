#pragma once

#include "../NEAdam/NEAdam.hpp"

namespace NE
{
	template <typename T>
	class NETUnknownMetaClass;

	class NE_DLL NEUnknown : public NEAdam
	{
	public:
		typedef NEUnknown This;
		typedef NEAdam Super;
		typedef NETUnknownMetaClass<NEUnknown> MetaClass;
	};
}