#pragma once

#pragma message("NEUnknown.hpp - 1")
#include "../NEAdam/NEAdam.hpp"
#pragma message("NEUnknown.hpp - 2")

namespace NE
{
	class NE_DLL NEUnknown : public NEAdam 
	{
		NE_NATIVE_DECLARE_ONLY(NEUnknown, NEAdam, NETUnknownMetaClass)
	};
}
#pragma message("NEUnknown.hpp - 3")