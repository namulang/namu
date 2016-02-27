#pragma once

#include "../../../Modules/NEStringSet/NEStringSet.hpp"
#include "../../../Modules/NEWStringSet/NEWStringSet.hpp"

namespace NE
{	
#ifdef _UNICODE
	typedef NEWStringSet NETStringSet;
#else
	typedef NEStringSet NETStringSet;
#endif
}
