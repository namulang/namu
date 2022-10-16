#pragma once

#include "../expr.hpp"

namespace namu {

    class visitor;

    class _nout defSeqExpr : public expr {
        NAMU(CLASS(defSeqExpr, expr, expr::exprType), VISIT())
        friend class mgdFunc;
        friend class verifier;

    public:
        defSeqExpr(const node& start, const node& end): _start(start), _end(end) {}

    public:
        using super::run;
        str run(const args& a) override;

        const node& getEval() const override;

        const node& getStart() const { return *_start; }
        const node& getEnd() const { return *_end; }

    private:
        str _start;
        str _end;
    };
}
