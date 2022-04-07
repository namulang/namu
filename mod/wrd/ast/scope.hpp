#pragma once

#include "../builtin/container/native/tnchain.hpp"
#include "immutableTactic.hpp"
#include "node.hpp"

namespace wrd {
    typedef tnmap<std::string, node, immutableTactic> scope;
    typedef tnchain<std::string, node, scope> scopes;
}
