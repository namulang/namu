#pragma once

#include "defThis.hpp"

#define WRD_DECL_ME_2(ME, SUPER) \
    public: \
        WRD_DEF_ME_2(ME, SUPER) \
    private:

#define WRD_DECL_ME_1(ME) \
    public: \
        WRD_DEF_ME_1(ME) \
    private:

#define WRD_DECL_ME(...)  WRD_OVERLOAD(WRD_DECL_ME, __VA_ARGS__)
