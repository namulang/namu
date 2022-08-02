#pragma once

#include "dep.hpp"
#include "common/_wout.hpp"

namespace namu {
    class type;
    typedef std::vector<type*> types;
}

#define WRD_INIT_META(me) \
    WRD_INITIATOR(initMeta, { \
        ::namu::ttype<me>().init(); \
    })

// namuMeta macro's sub-commands:
//  INIT META: it redirects to WRD_INIT_META macro.
#define __WRD__DECL_INIT_META(ME) WRD_INIT_META(ME)
