#pragma once

#include "dep.hpp"

namespace wrd {
    class Type;
    typedef std::vector<Type*> Types;
}

#define WRD_INIT_META(This) \
    WRD_INITIATOR(initMeta, { \
        ::wrd::TType<This>().init(); \
    })
