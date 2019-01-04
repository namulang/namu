#pragma once

#include "Overload.hpp"

#define WRD_ASSIGN_GUARD_0()	AGN_GUARD_1(rhs)
#define WRD_ASSIGN_GUARD_1(rhs)	if(this == &rhs) return *this;
#define WRD_ASSIGN_GUARD(...)	WRD_OVERLOAD(WRD_ASSIGN_GUARD, __VA_ARGS__)
