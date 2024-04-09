#pragma once

#include "retStateExpr.hpp"
#include "../../builtin/primitive/nVoid.hpp"

namespace namu {

    class _nout nextRet : public nVoid {
        NAMU(CLASS(nextRet, nVoid))
    };

    class _nout nextExpr : public retStateExpr {
        NAMU(CLASS(nextExpr, retStateExpr, expr::exprType), VISIT())

    protected:
        const node& _onGetRet() const override;
    };
}
