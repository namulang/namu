#pragma once

#include "../common.hpp"

namespace namu {

    class binder;
    class instance;
    class _wout bindTacticable {
    public:
        virtual void rel(binder& me) = 0;
        virtual wbool bind(binder& me, const instance& it) = 0;
    };
}
