#pragma once

#include "WeakTactic.hpp"

namespace wrd {

    class StrTactic : public WeakTactic {
        WRD_DECL_THIS(StrTactic, WeakTactic);

    public:
        wbool unbind(Bind& me);
        wbool bind(Bind& me, Instance& it);

        static This singletone;
    };
}
