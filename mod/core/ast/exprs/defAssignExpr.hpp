#pragma once

#include "../expr.hpp"
#include "../param.hpp"
#include "../scope.hpp"

namespace namu {

    class visitor;

    /// in fact, defAssign is a stmt, not a expression.
    class _nout defAssignExpr : public expr {
        NAMU(CLASS(defAssignExpr, expr, expr::exprType), VISIT())
        friend class verifier;
        friend class mgdFunc;
        typedef scopes::iter iter;

    public:
        defAssignExpr(const std::string& name, const node& rhs, nbool isOnDefBlock = false): _rhs(rhs),
                _isOnDefBlock(isOnDefBlock), _name(name) {}
        defAssignExpr(const node& to, const std::string& name, const node& rhs, nbool isOnDefBlock = false):
                _to(to), _rhs(rhs), _isOnDefBlock(isOnDefBlock), _name(name) {}

    public:
        using super::run;
        str run(const args& a) override;

        const node& getEval() const override { return _rhs->getEval(); }
        const std::string& getSubName() const { return _name; }
        const node& getRight() const { return *_rhs; }
        node& getRight() { return *_rhs; }
        const node& getTo() const NAMU_UNCONST_FUNC(getTo())
        nbool isOnDefBlock() const { return _isOnDefBlock; }
        node& getTo();

        clonable* deepClone() const override {
            NAMU_DW("defAssignExpr: deepClone");

            me* ret = (me*) clone();
            if(_to) ret->_to.bind((node*) _to->deepClone());
            if(_rhs) ret->_rhs.bind((node*) _rhs->deepClone());

            return ret;
        }

    private:
        str _to;
        str _rhs;
        nbool _isOnDefBlock;
        std::string _name; // name of variable or lambda.
    };
}
