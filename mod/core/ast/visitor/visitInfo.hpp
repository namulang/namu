#pragma once

#include "../../common.hpp"

namespace namu {
    struct visitInfo {
        std::string name;
        node* parent;
        nint index;
        nint depth;
    };
}
