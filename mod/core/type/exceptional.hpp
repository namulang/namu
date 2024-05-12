#pragma once

#include "../common.hpp"

namespace namu {
    struct point;
    class _nout exceptional {
        NAMU(ME(exceptional))

    public:
        void ex(nint code, ...);
        void ex(const point& src, int code, ...);
    };
}
