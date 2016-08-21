#pragma once

#include "../NEAdam/NEAdam.hpp"

namespace NE
{
	class NE_DLL NEUnknown : public NEAdam 
	{
		NE_NATIVE_DECLARE_ONLY(NEUnknown, NEAdam, NETUnknownMetaClass)
	};
}