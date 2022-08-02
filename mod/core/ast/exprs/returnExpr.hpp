#pragma once

#include "../expr.hpp"

namespace namu {

    class _wout returnExpr : public expr {
        WRD(CLASS(returnExpr, expr, expr::exprType))

    public:
        returnExpr(const node& ret);
        returnExpr();

    public:
        using super::run;
        str run(const ucontainable& args) override;

        node& getRet();
        const node& getRet() const WRD_UNCONST_FUNC(getRet())
        wbool canRun(const ucontainable& args) const override;
        const node& getEval() const override;

    private:
        str _decideRet(const ucontainable& args);

    private:
        str _ret;
    };
}
