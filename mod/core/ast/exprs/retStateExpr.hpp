#pragma once

#include "../expr.hpp"

namespace namu {

    class _nout retStateExpr : public expr {
        NAMU(ADT(retStateExpr, expr), VISIT())

    public:
        using super::run;
        str run(const args& a) override;

        priority prioritize(const args& a) const override;
        str getEval() const override;

    protected:
        virtual const node& _onGetRet() const = 0;
    };
}
