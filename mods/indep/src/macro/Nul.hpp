#pragma once

#include "Overload.hpp"

#define WRD_NUL_2(var, ret) \
    if(nul(var)) { \
        WRD_W(var " is nul"); \
        return ret; \
    }
#define WRD_NUL_1(var) WRD_NUL_2(var, WRD_VOID())
#define WRD_NUL(...) WRD_OVERLOAD(WRD_NUL, __VA_ARGS__)

#define WRD_NUL_THEN_LOG(var) if(nul(var)) WRD_W(var " is nul");
