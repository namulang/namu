#pragma once

#include "../expr.hpp"

namespace nm {

    class visitor;

    class _nout defSeqExpr : public expr {
        NM(CLASS(defSeqExpr, expr, expr::exprType), VISIT())
        friend class func;
        friend class verifier;

    public:
        defSeqExpr(const node& start, const node& end);

    public:
        using super::run;
        str run(const args& a) override;

        str getEval() const override;

        const node& getStart() const;
        const node& getEnd() const;

    private:
        str _start;
        str _end;
    };
}
