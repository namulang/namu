#pragma once

#include "../common.hpp"

namespace namu {

    class _wout validable {
        WRD_DECL_ME(validable)
        WRD_INIT_META(me)

    public:
        virtual wbool isValid() const = 0;
    };
}
