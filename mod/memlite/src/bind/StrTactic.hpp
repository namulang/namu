#pragma once

#include "WeakTactic.hpp"

namespace wrd {

    class StrTactic : public WeakTactic {
        WRD_DECL_ME(StrTactic, WeakTactic);

    public:
        wbool unbind(Bind& me) override;
        wbool bind(Bind& me, const Instance& it) override;

        static me singletone;
    };
}
