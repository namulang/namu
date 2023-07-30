#pragma once

#include "../expr.hpp"
#include "../param.hpp"
#include "../../builtin/primitive/arithmeticObj.hpp"
#include "../scope.hpp"

namespace namu {

    class visitor;

    // FAO: Fundermental Unary Operation.
    class _nout FUOExpr : public expr {
        NAMU(CLASS(FUOExpr, expr, expr::exprType), VISIT())

    public:
        enum rule {
            POSTFIX_DOUBLE_PLUS = 0,
            START = POSTFIX_DOUBLE_PLUS,
            POSTFIX_DOUBLE_MINUS, BITWISE_NOT,
            END
        };

    public:
        FUOExpr(rule rule, const node& it);

    public:
        using super::run;
        str run(const args& a) override;

        str getEval() const override;
        rule getRule() const;

    private:
        rule _rule;
        str _it;
    };
}
