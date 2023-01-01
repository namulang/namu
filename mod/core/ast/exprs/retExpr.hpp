#pragma once

#include "retStateExpr.hpp"

namespace namu {

    class _nout retExpr : public retStateExpr {
        NAMU(CLASS(retExpr, retStateExpr, expr::exprType), VISIT())

    public:
        retExpr(const node& ret): super(ret) {}
        retExpr() {}

    protected:
        const retState& onGetRetState() const override;
    };
}
