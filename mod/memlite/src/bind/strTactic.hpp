#pragma once

#include "weakTactic.hpp"

namespace wrd {

    class strTactic : public weakTactic {
        WRD_DECL_ME(strTactic, weakTactic);

    public:
        wbool unbind(bind& me) override;
        wbool bind(bind& me, const instance& it) override;

        static me singletone;
    };
}
