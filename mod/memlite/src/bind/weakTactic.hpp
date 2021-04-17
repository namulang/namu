#pragma once

#include "bindTacticable.hpp"
#include "../interface/instance.hpp"

namespace wrd {

    class weakTactic : public bindTacticable {
        WRD_DECL_ME(weakTactic, bindTacticable);

    public:
        wbool unbind(bind& me) override;
        wbool bind(bind& me, const instance& it) override;

    public:
        static me singletone;
    };
}
