#pragma once

#include "dep.hpp"
#include "_nout.hpp"

namespace nm {

    const std::string MANIFEST_FILENAME = "manifest.leaf";

    class node;
    class ntype;
    typedef tstr<node> str;
    typedef tweak<node> weak;
}
