#pragma once

#include "core/common.hpp"

namespace nm {

    class _nout immutableTactic: public strTactic {
        NM(ME(immutableTactic, strTactic))

    public:
        using super::bind;
        nbool bind(binder& me, const instance& it) override;

    public:
        static me singleton;
    };
}
