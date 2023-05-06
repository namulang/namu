#pragma once

#include "../common/dep.hpp"

namespace namu {
    struct _nout point {
        nbool isOrigin() const { return row == 0 && col == 0; }
        void rel() { row = col = 0; }

    public:
        ncnt row;
        ncnt col;
    };

    struct _nout area {
        void rel() {
            start.rel();
            end.rel();
        }

    public:
        point start;
        point end;
    };
}
