#pragma once
//	include:
#include "../../../Modules/NECharKey/NECharKey.hpp"
#include "../../../Modules/NEWCharKey/NEWCharKey.hpp"

namespace NE
{
#ifdef _UNICODE
	typedef NEWCharKey NETCharKey;
#else	
	typedef NECharKey NETCharKey;
#endif
}