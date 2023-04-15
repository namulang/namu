#pragma once

#include "mgdFunc.hpp"

namespace namu {

    class _nout inputFunc : public func {
        NAMU(CLASS(inputFunc, mgdFunc))

    public:
        const params& getParams() const override;

        const node& getRet() const override;

        str run(const args& a) override;
    };
}
