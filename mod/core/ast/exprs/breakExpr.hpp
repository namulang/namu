#pragma once

#include "retStateExpr.hpp"
#include "../../builtin/primitive/nVoid.hpp"

namespace namu {

    class breakRet : public nVoid {
        NAMU(CLASS(breakRet, nVoid))
    };

    class _nout breakExpr : public retStateExpr {
        NAMU(CLASS(breakExpr, retStateExpr, expr::exprType), VISIT())

    protected:
        const node& _onGetRet() const override;
    };
}
