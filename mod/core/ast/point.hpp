#pragma once

#include "../common/dep.hpp"

namespace namu {
    struct _wout point {
        wcnt row;
        wcnt col;

        void rel() {
            row = col = 0;
        }
    };

    struct _wout area {
        point start;
        point end;

        void rel() {
            start.rel();
            end.rel();
        }
    };
}
