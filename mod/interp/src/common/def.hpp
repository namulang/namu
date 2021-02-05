#pragma once

#include "dep.hpp"

#define WRD_CLASS_1(THIS) \
    WRD_DECL_THIS_1(THIS) \
    WRD_INIT_META(THIS)

#define WRD_CLASS_2(THIS, SUPER) \
    WRD_DECL_THIS_2(THIS, SUPER) \
    WRD_INIT_META(THIS)

#define WRD_CLASS(...) WRD_OVERLOAD(WRD_CLASS, __VA_ARGS__)
