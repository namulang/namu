#pragma once

#include "../expr.hpp"

namespace wrd {

    class blockExpr : public expr {
        WRD(CLASS(blockExpr, expr, expr::exprType),
            FRIEND_VERIFY(blockExpr, visitSubNodes))
        friend class mgdFunc;

    public:
        blockExpr() {}
        blockExpr(std::initializer_list<const expr*> elems): _exprs(elems) {}
        template <typename... Es>
        blockExpr(const Es&... elems): _exprs(elems...) {}

    public:
        using super::run;
        str run(const ucontainable& args) override;

        const wtype& getEvalType() const override {
            wcnt len = _exprs.len();
            if(len <= 0) return nulOf<wtype>();

            return _exprs[len-1].getEvalType();
        }

        const narr& getBlocks() const { return _exprs; }
        narr& getBlocks() { return _exprs; }

    private:
        wbool _inFrame();
        void _outFrame();

    private:
        narr _exprs;
    };
}
