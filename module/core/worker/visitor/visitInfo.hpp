#pragma once

#include "core/common.hpp"

namespace nm {
    struct _nout visitInfo {
        std::string name;
        node* parent;
        nidx index;
        ncnt len;
        nint depth;
    };
}
