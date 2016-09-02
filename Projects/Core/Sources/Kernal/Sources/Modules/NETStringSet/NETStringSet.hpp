#pragma once

#include "../NEStringSet/NEStringSet.hpp"
#include "../NEWStringSet/NEWStringSet.hpp"

namespace NE
{	
#ifdef _UNICODE
	typedef NEWStringSet NETStringSet;
#else
	typedef NEStringSet NETStringSet;
#endif
}
