#pragma once

#include "../expr.hpp"
#include "../param.hpp"
#include "../../builtin/primitive/arithmeticObj.hpp"
#include "../scope.hpp"

namespace namu {

    class visitor;

    // FAO: Fundermental Binary Operation.
    class _nout FBOExpr : public expr {
        NAMU(CLASS(FBOExpr, expr, expr::exprType), VISIT())

    public:
        enum rule {
            ADD = 0,
            START = ADD,
            ARITH_START = START,
            SUB,
            MUL,
            DIV,
            MOD,
            ARITH_END,
            EQ,
            LOGIC_START = EQ,
            NE,
            GT,
            LT,
            GE,
            LE,
            AND,
            OR,
            LOGIC_END,
            END = LOGIC_END
        };

    public:
        FBOExpr(rule rule, const node& lhs, const node& rhs): _rule(rule), _lhs(str(lhs)), _rhs(str(rhs)) {}

    public:
        using super::run;
        str run(const args& a) override;

        str getEval() const override;
        const node& getLeft() const { return *_lhs; }
        void setLeft(const node& new1) { _lhs.bind(new1); }
        const node& getRight() const { return *_rhs; }
        void setRight(const node& new1) { _rhs.bind(new1); }
        nbool isLogicalOp() const;
        rule getRule() const { return _rule; }

    private:
        rule _rule;
        str _lhs;
        str _rhs;
    };
}
