#pragma once

#include "weakTactic.hpp"

namespace wrd {

    class strTactic : public weakTactic {
        WRD_DECL_ME(strTactic, weakTactic);

    public:
        void rel(binder& me) override;
        wbool bind(binder& me, const instance& it) override;

        static me singletone;
    };
}
