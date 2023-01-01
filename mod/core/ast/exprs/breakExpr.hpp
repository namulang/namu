#pragma once

#include "retStateExpr.hpp"

namespace namu {

    class _nout breakExpr : public retStateExpr {
        NAMU(CLASS(breakExpr, retStateExpr, expr::exprType), VISIT())

    public:
        breakExpr(const node& ret): super(ret) {}
        breakExpr() {}

    protected:
        const retState& onGetRetState() const override;
    };
}
