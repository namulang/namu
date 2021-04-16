#pragma once

#include "../common.hpp"

namespace wrd {

    class Clonable {
        WRD_DECL_ME(Clonable)
        WRD_INIT_META(me)

    public:
        virtual ~Clonable() {}

        virtual me* clone() const = 0;
    };
}
