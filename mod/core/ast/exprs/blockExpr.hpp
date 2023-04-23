#pragma once

#include "../expr.hpp"

namespace namu {

    class visitor;

    class _nout blockExpr : public expr {
        NAMU(CLASS(blockExpr, expr, expr::exprType), VISIT())
        friend class verifier;
        friend class mgdFunc;

    public:
        blockExpr() {}
        template <typename... Es>
        blockExpr(const Es&... elems): _exprs(elems...) {}

    public:
        using super::run;
        str run(const args& a) override;
        str getEval() const override;
        const narr& getStmts() const { return _exprs; }
        narr& getStmts() { return _exprs; }

        void inFrame(const bicontainable& args) override;
        void outFrame() override;

        clonable* deepClone() const override {
            NAMU_DW("blockExpr: deepClone");

            me* ret = (me*) clone();
            ret->_exprs.rel();
            for(auto e=_exprs.begin(); e ;e++)
                ret->_exprs.add((node*) e->deepClone());

            return ret;
        }

    private:
        narr _exprs;
    };
}
