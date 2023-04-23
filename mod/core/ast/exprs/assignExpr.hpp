#pragma once

#include "../expr.hpp"
#include "../param.hpp"
#include "../scope.hpp"

namespace namu {

    class visitor;

    class _nout assignExpr : public expr {
        NAMU(CLASS(assignExpr, expr, expr::exprType), VISIT())
        friend class verifier;
        friend class mgdFunc;
        typedef scopes::iter iter;

    public:
        assignExpr(const node& lhs, const node& rhs): _lhs(lhs), _rhs(rhs) {}

    public:
        using super::run;
        str run(const args& a) override {
            iter e = _getScopeIterOfLhs(); // e exists. verified.

            str ret = _rhs->run();
            e.setVal(*ret);
            return ret;
        }
        str getEval() const override {
            return _rhs->getEval();
        }

        const node& getLeft() const {
            return *_lhs;
        }

        const node& getRight() const {
            return *_rhs;
        }

        clonable* deepClone() const override {
            me* ret = (me*) clone();
            if(_lhs) ret->_lhs.bind((node*) _lhs->deepClone());
            if(_rhs) ret->_rhs.bind((node*) _rhs->deepClone());
            return ret;
        }

    private:
        iter _getScopeIterOfLhs();

    private:
        str _lhs; // name of variable or lambda.
        str _rhs;
    };
}
