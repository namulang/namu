#pragma once

#include "src.hpp"

namespace namu {
    class _nout dumSrc : public src {
        NAMU(CLASS(dumSrc, src))

    private:
        dumSrc();

    public:
        static me& singletone();
    };
}
