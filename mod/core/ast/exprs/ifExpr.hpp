#pragma once

#include "../expr.hpp"
#include "blockExpr.hpp"

namespace namu {

    class _nout ifExpr : public expr {
        NAMU(CLASS(ifExpr, expr, expr::exprType), VISIT())
        friend class verifier;

    public:
        ifExpr(const node& exp, const blockExpr& thenBlk);
        ifExpr(const node& exp, const blockExpr& thenBlk, const blockExpr& elseBlk);

    public:
        const blockExpr& getThenBlk() const NAMU_UNCONST_FUNC(getThenBlk())
        blockExpr& getThenBlk();
        void setThenBlk(const blockExpr& newThen);

        const blockExpr& getElseBlk() const NAMU_UNCONST_FUNC(getElseBlk())
        blockExpr& getElseBlk();
        void setElseBlk(const blockExpr& newElse);

        const node& getCondition() const NAMU_UNCONST_FUNC(getCondition())
        node& getCondition();
        void setCondition(const node& newCondition);

        using super::run;
        str run(const args& a) override;

        str getEval() const override;

    private:
        str _expr;
        tstr<blockExpr> _thenBlk;
        tstr<blockExpr> _elseBlk;
    };
}
