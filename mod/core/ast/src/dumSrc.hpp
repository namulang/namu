#pragma once

#include "src.hpp"

namespace namu {

    class _nout dumSrc : public src {
        NAMU(CLASS(dumSrc, src))

    public:
        dumSrc();

    protected:
        void _setFile(const srcFile& new1) override;
        void _setPos(const point& new1) override;
    };
}
