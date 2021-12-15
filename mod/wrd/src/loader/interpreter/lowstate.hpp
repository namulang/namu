#pragma once

#include "tokenDispatcher.hpp"
#include "indenter.hpp"

namespace wrd {
    struct lowstate {
        str root;
        indenter ind;
        tokenDispatcher dispatcher;
    };
}
