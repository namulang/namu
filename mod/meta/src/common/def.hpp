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
