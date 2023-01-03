#pragma once

#include "retStateExpr.hpp"

namespace namu {

    class _nout nextExpr : public retStateExpr {
        NAMU(CLASS(nextExpr, retStateExpr, expr::exprType), VISIT())

    public:
        nextExpr(const node& ret): super(ret) {}
        nextExpr() {}

    protected:
        const retState& _onGetRetState() const override;
    };
}
