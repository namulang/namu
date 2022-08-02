#pragma once

#include "dep.hpp"
#include "_wout.hpp"

namespace namu {

    const std::string MANIFEST_FILENAME = "manifest.seedling";

    class node;
    class wtype;
    typedef tstr<node> str;
    typedef tweak<node> weak;
}
