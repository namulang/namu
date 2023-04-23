#pragma once

#include "loopExpr.hpp"

namespace namu {

    class _nout whileExpr : public loopExpr {
        NAMU(CLASS(whileExpr, loopExpr, expr::exprType), VISIT())
        friend class verifier;

    public:
        whileExpr(const node& condition, const blockExpr& blk);

    public:
        const node& getCondition() const NAMU_UNCONST_FUNC(getCondition())
        node& getCondition() { return *_condition; }

        using super::run;
        str run(const args& a) override;

        str getEval() const override;

    private:
        str _condition;
        mutable nbool _initEval;
    };
}
