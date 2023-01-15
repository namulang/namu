#pragma once

#include "loopExpr.hpp"

namespace namu {

    class _nout whileExpr : public loopExpr {
        NAMU(CLASS(whileExpr, loopExpr, expr::exprType), VISIT())
        friend class verifier;

    public:
        whileExpr(const node& condition, const blockExpr& blk);

    public:
        const node& getCondition() const { return *_condition; }

        using super::run;
        str run(const args& a) override;

        const node& getEval() const override;

    private:
        str _condition;
    };
}
