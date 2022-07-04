#pragma once

#include "../expr.hpp"
#include "../param.hpp"
#include "../scope.hpp"

namespace wrd {

    class _wout asExpr : public expr {
        WRD(CLASS(asExpr, expr),
            FRIEND_VERIFY(asExpr, verifyIter))
        friend class mgdFunc;
        typedef scopes::iter iter;

    public:
        asExpr(const node& me, const node& as): _me(me), _as(as) {}

    public:
        using super::run;
        str run(const ucontainable& args) override {
            if(!_me || !_as) return str();

            return str(_me->as(*_as));
        }

        const wtype& getEvalType() const override { return _as->getType(); }
        const node& getMe() const { return *_me; }
        const node& getAs() const { return *_as; }

    private:
        str _me;
        str _as;
    };
}
