#pragma once

#include "bindTacticable.hpp"
#include "../interface/instance.hpp"

namespace wrd {

    class weakTactic : public bindTacticable {
        WRD_DECL_ME(weakTactic, bindTacticable);

    public:
        void rel(binder& me) override;
        wbool bind(binder& me, const instance& it) override;

    public:
        static me singletone;
    };
}
