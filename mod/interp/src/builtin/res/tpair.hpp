#pragma once

#include "../../common.hpp"

namespace wrd {

    template <typename L, typename R>
    struct tpair {
        tpair(): l(L()), r(R()) {}
        tpair(L newL, R newR): l(newL), r(newR) {}

        L l;
        R r;
    };
}
