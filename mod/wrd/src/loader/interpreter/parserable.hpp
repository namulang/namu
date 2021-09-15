#pragma once

#include <iostream>

namespace wrd {

    class node;
    template <typename T> class tstr;
    typedef tstr<node> str;

    class parserable {
    public:
        virtual str& getRootBinder() = 0;
    };
}
