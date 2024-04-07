#pragma once

#include "retStateExpr.hpp"
#include "../dumNode.hpp"

namespace namu {

    class nextRet : public dumNode {
        NAMU(CLASS(nextRet, dumNode))
    };

    class _nout nextExpr : public retStateExpr {
        NAMU(CLASS(nextExpr, retStateExpr, expr::exprType), VISIT())

    protected:
        const node& _onGetRet() const override;
    };
}
