#pragma once

#include "VSExpHack.hpp"

#define _STRINGIZER(x)	#x
#define WRD_MACRO_STRINGIZER(x)	WRD_VS_EXP_HACK(_STRINGIZER(x))
