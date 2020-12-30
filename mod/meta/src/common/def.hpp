#pragma once

#include "dep.hpp"

namespace wrd { namespace meta {
    class Type;
    typedef std::vector<Type*> Types;
}}

#define WRD_INIT_META(This) \
    WRD_INITIATOR(initMeta, { \
        wrd::meta::TType<This>().init(); \
    })
