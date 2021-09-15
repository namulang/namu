#pragma once

#include "../common.hpp"

namespace wrd {

    class clonable {
        WRD_DECL_ME(clonable)
        WRD_INIT_META(me)

    public:
        virtual ~clonable() {}

        virtual me* clone() const = 0;
    };
}
