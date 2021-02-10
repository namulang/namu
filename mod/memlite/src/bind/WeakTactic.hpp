#pragma once

#include "BindTacticable.hpp"
#include "../interface/Instance.hpp"

namespace wrd {

    class WeakTactic : public BindTacticable {
        WRD_DECL_THIS(WeakTactic, BindTacticable);

    public:
        wbool assign(Bind& me, Bind& rhs);
        wbool unbind(Bind& me);
        wbool bind(Bind& me, Instance& it);

    public:
        static This singletone;
    };
}
