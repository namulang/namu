#pragma once

#include "VSExpHack.hpp"

#define _CONCATERATOR(x, y)	x##y
#define NE_MACRO_CONCATERATOR(x, y)	NE_VS_EXP_HACK(_CONCATERATOR(x, y))