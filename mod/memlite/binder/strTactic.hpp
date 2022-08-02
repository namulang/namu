#pragma once

#include "weakTactic.hpp"

namespace namu {

    class _wout strTactic : public weakTactic {
        WRD_DECL_ME(strTactic, weakTactic);

    public:
        void rel(binder& me) override;
        wbool bind(binder& me, const instance& it) override;

        static me singletone;
    };
}
