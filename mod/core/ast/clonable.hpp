#pragma once

#include "../common.hpp"

namespace namu {

    class _wout clonable {
        WRD_DECL_ME(clonable)
        WRD_INIT_META(me)

    public:
        virtual ~clonable() {}

        virtual me* clone() const = 0;
    };
}
