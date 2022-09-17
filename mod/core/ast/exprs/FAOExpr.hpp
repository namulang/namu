#pragma once

#include "../expr.hpp"
#include "../param.hpp"
#include "../../builtin/primitive/arithmeticObj.hpp"
#include "../scope.hpp"

namespace namu {

    class visitor;

    // FAO: Five fundermental Arithmetic Operation.
    class _nout FAOExpr : public expr {
        NAMU(CLASS(FAOExpr, expr, expr::exprType), VISIT())

    public:
        enum Rule {
            ADD = 0,
            START = ADD,
            SUB,
            MUL,
            DIV,
            MOD,
            END
        };

    public:
        FAOExpr(Rule rule, const node& lhs, const node& rhs): mRule(rule), _lhs(str(lhs)), _rhs(str(rhs)) {}

    public:
        using super::run;
        str run(const args& a) override {
            if(!_lhs || !_rhs) return str();

            tstr<arithmeticObj> lhs(_lhs->run());
            tstr<arithmeticObj> rhs(_rhs->run());
            if(!lhs || !rhs) return str();

            switch(mRule) {
                case ADD: return lhs->add(*rhs);
                case SUB: return lhs->sub(*rhs);
                case MUL: return lhs->mul(*rhs);
                case DIV: return lhs->div(*rhs);
                case MOD: return lhs->mod(*rhs);
                default:
                    return str();
            }
        }

        const node& getEval() const override;
        const node& getLeft() const { return *_lhs; }
        void setLeft(const node& new1) { _lhs.bind(new1); }
        const node& getRight() const { return *_rhs; }
        void setRight(const node& new1) { _rhs.bind(new1); }

    private:
        Rule mRule;
        str _lhs;
        str _rhs;
    };
}
