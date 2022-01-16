#pragma once

#include "../common.hpp"

namespace wrd {

    class binder;
    class instance;
    class bindTacticable {
    public:
        virtual void rel(binder& me) = 0;
        virtual wbool bind(binder& me, const instance& it) = 0;
    };
}
