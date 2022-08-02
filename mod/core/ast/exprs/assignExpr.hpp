#pragma once

#include "../expr.hpp"
#include "../param.hpp"
#include "../scope.hpp"

namespace namu {

    class _wout assignExpr : public expr {
        WRD(CLASS(assignExpr, expr, expr::exprType),
            FRIEND_VERIFY(assignExpr, verifyIter))
        friend class mgdFunc;
        typedef scopes::iter iter;

    public:
        assignExpr(const node& lhs, const node& rhs): _lhs(lhs), _rhs(rhs) {}

    public:
        using super::run;
        str run(const ucontainable& args) override {
            iter e = _getScopeIterOfLhs(); // e exists. verified.

            str ret = _rhs->run();
            e.setVal(*ret);
            return ret;
        }
        const node& getEval() const override {
            return _rhs->getEval();
        }

        const node& getLeft() const {
            return *_lhs;
        }

        const node& getRight() const {
            return *_rhs;
        }

    private:
        iter _getScopeIterOfLhs();

    private:
        str _lhs; // name of variable or lambda.
        str _rhs;
    };
}
