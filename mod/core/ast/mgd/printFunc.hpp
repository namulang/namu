#pragma once

#include "mgdFunc.hpp"

namespace namu {

    class _nout printFunc : public func {
        NAMU(CLASS(printFunc, mgdFunc))

    public:
        const params& getParams() const override;

        const node& getRet() const override;

        str run(const args& a) override;
    };
}
