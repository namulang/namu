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

        str getEval() const override { return _as; }
        const node& getMe() const { return *_me; }
        const node& getAs() const { return *_as; }
        void setAs(const node& new1) { _as.bind(new1); }

        clonable* deepClone() const override {
            me* ret = (me*) clone();
            if(_me) ret->_me.bind((node*) _me->deepClone());
            if(_as) ret->_as.bind((node*) _as->deepClone());
            return ret;
        }

    private:
        str _me;
        str _as;
    };
}
