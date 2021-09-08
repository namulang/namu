#pragma once

#include "dep.hpp"

namespace wrd {
    class type;
    typedef std::vector<type*> types;
}

#define WRD_INIT_META(me) \
    WRD_INITIATOR(initMeta, { \
        ::wrd::ttype<me>().init(); \
    })

// wrdMeta macro's sub-commands:
//  INIT META: it redirects to WRD_INIT_META macro.
#define __WRD__DECL_INIT_META(ME) WRD_INIT_META(ME)
