#pragma once

#include "../../../ast/baseFunc.hpp"

namespace nm {

    class _nout inputFunc: public baseFunc {
        NM(ME(inputFunc, baseFunc), CLONE(inputFunc))

    public:
        using super::getParams;
        params& getParams() override;

        str getRet() const override;

        str run(const args& a) override;
    };
}
