#pragma once

#include "../builtin/container/native/tnchain.hpp"
#include "node.hpp"

namespace wrd {
    typedef tnchain<std::string, node, immutableTactic> scope;
}
