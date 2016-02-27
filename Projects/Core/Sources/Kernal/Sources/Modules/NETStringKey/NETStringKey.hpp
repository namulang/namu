#pragma once
//	include:
#include "../../../Modules/NEStringKey/NEStringKey.hpp"
#include "../../../Modules/NEWStringKey/NEWStringKey.hpp"

namespace NE
{
#ifdef _UNICODE
	typedef NEWStringKey NETStringKey;
#else	
	typedef NEStringKey NETStringKey;
#endif
}