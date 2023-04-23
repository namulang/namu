#pragma once

#include "../../ast/func.hpp"

namespace namu {

    class _nout inputFunc : public func {
        NAMU(CLASS(inputFunc, func))

    public:
        const params& getParams() const override;

        str getRet() const override;

        str run(const args& a) override;
    };
}
