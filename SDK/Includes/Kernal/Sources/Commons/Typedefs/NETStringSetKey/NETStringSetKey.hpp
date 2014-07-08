#pragma once
//	include:
#include "../../../Modules/NEStringSetKey/NEStringSetKey.hpp"
#include "../../../Modules/NEWStringSetKey/NEWStringSetKey.hpp"

namespace NE
{
#ifdef _UNICODE
	typedef NEWStringSetKey NETStringSetKey;
#else	
	typedef NEStringSetKey NETStringSetKey;
#endif
}