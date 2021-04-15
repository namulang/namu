#pragma once

#include "overload.hpp"

#define WRD_DEF_THIS_2(THIS, SUPER) \
    WRD_DEF_THIS_1(WRD_UNWRAP(THIS)) \
    typedef WRD_UNWRAP(SUPER) super;

#define WRD_DEF_THIS_1(THIS) typedef WRD_UNWRAP(THIS) me;

#define WRD_DEF_THIS(...) WRD_OVERLOAD(WRD_DEF_THIS, __VA_ARGS__)
