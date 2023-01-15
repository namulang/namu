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

    protected:
        /// @return true if exit the loop
        nbool _postProcess(frame& fr) const;

    private:
        mutable tstr<blockExpr> _blk;
    };
}
