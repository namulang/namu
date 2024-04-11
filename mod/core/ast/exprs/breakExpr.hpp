#pragma once

#include "retStateExpr.hpp"

namespace namu {

    class _nout breakRet : public retState {
        NAMU(CLASS(breakRet, retState))
    };

    class _nout breakExpr : public retStateExpr {
        NAMU(CLASS(breakExpr, retStateExpr, expr::exprType), VISIT())

    protected:
        const node& _onGetRet() const override;
    };
}
