#pragma once

#include "VSExpHack.hpp"

#define _CONCATERATOR(x, y)	x##y
#define WRD_MACRO_CONCATERATOR(x, y)	WRD_VS_EXP_HACK(_CONCATERATOR(x, y))
