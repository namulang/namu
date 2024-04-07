#pragma once

#include "retStateExpr.hpp"
#include "../dumNode.hpp"

namespace namu {

    class breakRet : public dumNode {
        NAMU(CLASS(breakRet, dumNode))
    };

    class _nout breakExpr : public retStateExpr {
        NAMU(CLASS(breakExpr, retStateExpr, expr::exprType), VISIT())

    protected:
        const node& _onGetRet() const override;
    };
}
