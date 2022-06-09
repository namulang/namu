#pragma once

#include "../builtin/container/native/tnchain.hpp"
#include "immutableTactic.hpp"
#include "../builtin/container/native/tndumMap.hpp"
#include "node.hpp"

namespace wrd {
    typedef tnmap<std::string, node, immutableTactic> scope;
    typedef tndumMap<std::string, node, immutableTactic> dumScope;
    typedef tnchain<std::string, node, scope> scopes;
}
