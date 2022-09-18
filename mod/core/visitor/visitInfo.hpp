#pragma once

#include "../common.hpp"

namespace namu {
    struct visitInfo {
        std::string name;
        node* parent;
        nidx index;
        ncnt len;
        nint depth;
    };
}
