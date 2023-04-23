#pragma once

#include "../expr.hpp"

namespace namu {

    class retState;
    class _nout retStateExpr : public expr {
        NAMU(ADT(retStateExpr, expr, expr::exprType), VISIT())

    public:
        retStateExpr(const node& ret);
        retStateExpr();

    public:
        using super::run;
        str run(const args& a) override;

        node& getRet();
        const node& getRet() const NAMU_UNCONST_FUNC(getRet())
        nbool canRun(const args& a) const override;
        str getEval() const override;

    protected:
        virtual const retState& _onGetRetState() const = 0;

    private:
        str _decideRet(const args& a);

    private:
        str _ret;
    };
}
