#pragma once

#include "../expr.hpp"
#include "blockExpr.hpp"

namespace namu {

    class frame;
    class _nout loopExpr : public expr {
        NAMU(ADT(loopExpr, expr, expr::exprType), VISIT())

    public:
        loopExpr(const blockExpr& blk): _blk(blk) {}

    public:
        blockExpr& getBlock() const { return *_blk; }
        const node& getEval() const override { return *_eval; }
        nbool setEval(const node& new1) const { return _eval.bind(new1); }

    protected:
        /// @return true if exit the loop
        nbool _postProcess(frame& fr) const;

    private:
        mutable tstr<blockExpr> _blk;
        mutable str _eval;
    };
}
