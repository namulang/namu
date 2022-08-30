#pragma once

#include "../expr.hpp"

namespace namu {

    class visitor;

    class _nout blockExpr : public expr {
        NAMU(CLASS(blockExpr, expr, expr::exprType), VISIT(),
            FRIEND_VERIFY(blockExpr, visitSubNodes))
        friend class mgdFunc;

    public:
        blockExpr() {}
        template <typename... Es>
        blockExpr(const Es&... elems): _exprs(elems...) {}

    public:
        using super::run;
        str run(const args& a) override;
        const node& getEval() const override;
        const narr& getStmts() const { return _exprs; }
        narr& getStmts() { return _exprs; }

    private:
        void _inFrame(const bicontainable& args) override;
        void _outFrame() override;

    private:
        narr _exprs;
    };
}
