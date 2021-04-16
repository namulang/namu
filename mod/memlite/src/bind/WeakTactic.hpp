#pragma once

#include "BindTacticable.hpp"
#include "../interface/Instance.hpp"

namespace wrd {

    class WeakTactic : public BindTacticable {
        WRD_DECL_ME(WeakTactic, BindTacticable);

    public:
        wbool unbind(Bind& me) override;
        wbool bind(Bind& me, const Instance& it) override;

    public:
        static me singletone;
    };
}
