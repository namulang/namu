#pragma once

#include "../../common.hpp"

namespace wrd {

    template <typename L, typename R>
    struct tpair {
        tpair() {}
        tpair(L& newL, R& newR): l(newL), r(newR) {}

        L l;
        R r;
    };

    template <typename L, typename R>
    struct tpair<L&, R> {
        tpair(): l(nulOf<L>()) {}
        tpair(L& newL, R newR): l(newL), r(newR) {}

        L& l;
        R r;
    };

    template <typename L, typename R>
    struct tpair<L, R&> {
        tpair(): r(nulOf<R>()) {}
        tpair(L newL, R& newR): l(newL), r(newR) {}

        L l;
        R& r;
    };

    template <typename L, typename R>
    struct tpair<L&, R&> {
        tpair(): l(nulOf<L>()), r(nulOf<R>()) {}
        tpair(L& newL, R& newR): l(newL), r(newR) {}

        L& l;
        R& r;
    };
}
