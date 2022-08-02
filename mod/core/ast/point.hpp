#pragma once

#include "../common/dep.hpp"

namespace namu {
    struct _nout point {
        ncnt row;
        ncnt col;

        void rel() {
            row = col = 0;
        }
    };

    struct _nout area {
        point start;
        point end;

        void rel() {
            start.rel();
            end.rel();
        }
    };
}
