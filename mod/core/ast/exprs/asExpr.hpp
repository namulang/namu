#pragma once

#include "../expr.hpp"
#include "../param.hpp"
#include "../scope.hpp"

namespace namu {

    class visitor;

    class _nout asExpr : public expr {
        NAMU(CLASS(asExpr, expr, expr::exprType), VISIT())
        friend class verifier;
        friend class mgdFunc;
        typedef scopes::iter iter;

    public:
        asExpr(const node& me, const node& as): _me(me), _as(as) {}

    public:
        using super::run;
        str run(const args& a) override {
            if(!_me || !_as) return str();

            str eval = _me->run();
            if(!eval) return NAMU_E("!eval.isBind()"), str();

            return str(eval->as(*_as));
        }

        const node& getEval() const override { return getAs(); }
        const node& getMe() const { return *_me; }
        const node& getAs() const { return *_as; }
        void setAs(const node& new1) { _as.bind(new1); }

    private:
        str _me;
        str _as;
    };
}
