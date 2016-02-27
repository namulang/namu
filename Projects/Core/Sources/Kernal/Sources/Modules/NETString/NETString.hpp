#pragma once

#include "../NEString/NEString.hpp"
#include "../NEWString/NEWString.hpp"

namespace NE
{	
#ifdef _UNICODE
	typedef NEWString NETString;
#else
	typedef NEString NETString;
#endif
}