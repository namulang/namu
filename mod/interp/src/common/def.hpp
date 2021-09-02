#pragma once

#include "decl.hpp"

namespace wrd {

    const std::string MANIFEST_FILENAME = "manifest.swrd";

    class node;
    class wtype;
    typedef tstr<node> str;
    typedef tweak<node> weak;
}
