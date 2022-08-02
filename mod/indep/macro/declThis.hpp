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

// namuMeta macro's sub-commands:
//  ME: actually it redirects builtin macro 'WRD_DECL_ME'.
#define __WRD__DECL_ME_1(ME) WRD_DECL_ME_1(ME)
#define __WRD__DECL_ME_2(ME, SUPER) WRD_DECL_ME_2(ME, SUPER)
#define __WRD__DECL_ME(...) WRD_OVERLOAD(__WRD__DECL_ME, __VA_ARGS__)
