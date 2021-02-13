#pragma once

#include "BindTacticable.hpp"
#include "../interface/Instance.hpp"

namespace wrd {

    class WeakTactic : public BindTacticable {
        WRD_DECL_THIS(WeakTactic, BindTacticable);

    public:
        wbool assign(Bind& me, const Bind& rhs);
        wbool unbind(Bind& me);
        wbool bind(Bind& me, const Instance& it);

    public:
        static This singletone;
    };
}
