#pragma once

#include "../expr.hpp"

namespace namu {

    class _nout returnExpr : public expr {
        NAMU(CLASS(returnExpr, expr, expr::exprType))

    public:
        returnExpr(const node& ret);
        returnExpr();

    public:
        using super::run;
        str run(const args& a) override;

        node& getRet();
        const node& getRet() const NAMU_UNCONST_FUNC(getRet())
        nbool canRun(const args& a) const override;
        const node& getEval() const override;

    private:
        str _decideRet(const args& a);

    private:
        str _ret;
    };
}
