#pragma once

#include "Overload.hpp"

#define WRD_NIL_2(var, ret) \
    if(nil(var)) { \
        WRD_W(var " is nil"); \
        return ret; \
    }
#define WRD_NIL_1(var) WRD_NIL_2(var, WRD_VOID())
#define WRD_NIL(...) WRD_OVERLOAD(WRD_NIL, __VA_ARGS__)

#define WRD_NIL_THEN_LOG(var) if(nul(var)) WRD_W(var " is nul");
