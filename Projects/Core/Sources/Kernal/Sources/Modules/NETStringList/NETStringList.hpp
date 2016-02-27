#pragma once

#include "../../../Modules/NEStringList/NEStringList.hpp"
#include "../../../Modules/NEWStringList/NEWStringList.hpp"

namespace NE
{	
#ifdef _UNICODE
	typedef NEWStringList NETStringList;
#else
	typedef NEStringList NETStringList;
#endif
}