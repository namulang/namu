#pragma message ("scope-1")
#pragma once

#pragma message ("scope0")
#include "../builtin/container/native/tnchain.hpp"
#pragma message ("scope1")
#include "immutableTactic.hpp"
#pragma message ("scope2")
#include "node.hpp"

#pragma message ("scope3")
namespace wrd {
    typedef tnmap<std::string, node, immutableTactic> scope;
    typedef tnchain<std::string, node, scope> scopes;
}
#pragma message ("scope4")
