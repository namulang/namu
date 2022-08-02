#pragma once

#include "../expr.hpp"
#include "../param.hpp"
#include "../scope.hpp"

namespace namu {

    class _wout defAssignExpr : public expr {
        WRD(CLASS(defAssignExpr, expr, expr::exprType),
            FRIEND_VERIFY(defAssignExpr, verifyIter))
        friend class mgdFunc;
        typedef scopes::iter iter;

    public:
        defAssignExpr(const std::string& name, const node& rhs, wbool isOnDefBlock = false): _rhs(rhs),
                _isOnDefBlock(isOnDefBlock), _name(name) {}
        defAssignExpr(const node& to, const std::string& name, const node& rhs, wbool isOnDefBlock = false):
                _to(to), _rhs(rhs), _isOnDefBlock(isOnDefBlock), _name(name) {}

    public:
        using super::run;
        str run(const ucontainable& args) override;

        const node& getEval() const override { return _rhs->getEval(); }
        const std::string& getSubName() const { return _name; }
        const node& getRight() const { return *_rhs; }
        node& getRight() { return *_rhs; }
        const node& getTo() const WRD_UNCONST_FUNC(getTo())
        wbool isOnDefBlock() const { return _isOnDefBlock; }
        node& getTo();

    private:
        str _to;
        str _rhs;
        wbool _isOnDefBlock;
        std::string _name; // name of variable or lambda.
    };
}
