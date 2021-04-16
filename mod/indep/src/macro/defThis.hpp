#pragma once

#include "overload.hpp"

#define WRD_DEF_ME_2(ME, SUPER) \
    WRD_DEF_ME_1(WRD_UNWRAP(ME)) \
    typedef WRD_UNWRAP(SUPER) super;

#define WRD_DEF_ME_1(ME) typedef WRD_UNWRAP(ME) me;

#define WRD_DEF_ME(...) WRD_OVERLOAD(WRD_DEF_ME, __VA_ARGS__)
