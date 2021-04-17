#pragma once

#include "../common.hpp"

namespace wrd {

    class binder;
    class instance;
    class bindTacticable {
    public:
        virtual wbool unbind(binder& me) = 0;
        virtual wbool bind(binder& me, const instance& it) = 0;
    };
}
