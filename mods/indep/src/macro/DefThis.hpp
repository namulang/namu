#pragma once

#include "Overload.hpp"

#define WRD_DEF_THIS_2(THIS, SUPER) \
    WRD_DEF_THIS_1(WRD_UNWRAP(THIS)) \
    typedef WRD_UNWRAP(SUPER) Super;

#define WRD_DEF_THIS_1(THIS) typedef WRD_UNWRAP(THIS) This;

#define WRD_DEF_THIS(...) WRD_OVERLOAD(WRD_DEF_THIS, __VA_ARGS__)
