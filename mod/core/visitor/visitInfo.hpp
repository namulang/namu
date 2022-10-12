#pragma once

#include "../common.hpp"

namespace namu {
    struct _nout visitInfo {
        std::string name;
        node* parent;
        nidx index;
        ncnt len;
        nint depth;
    };
}
