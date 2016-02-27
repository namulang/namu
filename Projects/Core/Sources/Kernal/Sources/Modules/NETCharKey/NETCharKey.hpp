#pragma once
//	include:
#include "../NECharKey/NECharKey.hpp"
#include "../NEWCharKey/NEWCharKey.hpp"

namespace NE
{
#ifdef _UNICODE
	typedef NEWCharKey NETCharKey;
#else	
	typedef NECharKey NETCharKey;
#endif
}