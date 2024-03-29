#pragma once

#include "../common.hpp"

namespace namu {

    class _nout validable {
        NAMU_ME(validable)
        NAMU_INIT_META(me)

    public:
        virtual nbool isValid() const = 0;
    };
}
