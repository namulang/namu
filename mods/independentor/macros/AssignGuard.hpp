#pragma once

#include "Overload.hpp"

#define WRD_ASSIGN_GUARD_0()			WRD_ASSIGN_GUARD_1(rhs)
#define WRD_ASSIGN_GUARD_1(rhs)			WRD_ASSIGN_GUARD_2(rhs, *this)
#define WRD_ASSIGN_GUARD_2(rhs, ret)	if(this == &rhs) return ret;
#define WRD_ASSIGN_GUARD(...)			WRD_OVERLOAD(WRD_ASSIGN_GUARD, __VA_ARGS__)
