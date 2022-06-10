#pragma once

#include "../expr.hpp"
#include "../param.hpp"
#include "../scope.hpp"

namespace wrd {

    class _wout defAssignExpr : public expr {
        WRD(CLASS(defAssignExpr, expr, expr::exprType),
            FRIEND_VERIFY(defAssignExpr, verifyIter))
        friend class mgdFunc;
        typedef scopes::iter iter;

    public:
        defAssignExpr(const std::string& name, const node& rhs): _name(name), _rhs(rhs) {}

    public:
        using super::run;
        str run(const ucontainable& args) override;

        const wtype& getEvalType() const override { return _rhs->getEvalType(); }
        const std::string& getSubName() const { return _name; }
        const node& getRight() const { return *_rhs; }
        node& getRight() { return *_rhs; }

    private:
        std::string _name; // name of variable or lambda.
        str _rhs;
    };
}
