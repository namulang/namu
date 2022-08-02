#pragma once

#include "../expr.hpp"

namespace namu {

    class _nout blockExpr : public expr {
        WRD(CLASS(blockExpr, expr, expr::exprType),
            FRIEND_VERIFY(blockExpr, visitSubNodes))
        friend class mgdFunc;

    public:
        blockExpr() {}
        template <typename... Es>
        blockExpr(const Es&... elems): _exprs(elems...) {}

    public:
        using super::run;
        str run(const ucontainable& args) override;
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
