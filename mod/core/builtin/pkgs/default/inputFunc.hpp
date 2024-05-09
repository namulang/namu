#pragma once

#include "../../../ast/baseFunc.hpp"

namespace namu {

    class _nout inputFunc : public baseFunc {
        NAMU(CLASS(inputFunc, baseFunc))

    public:
        const params& getParams() const override;

        str getRet() const override;

        str run(const args& a) override;
    };
}
