#pragma once

#include "../expr.hpp"

namespace wrd {

    class _wout literalExpr : public expr {
        WRD(CLASS(literalExpr, expr, expr::exprType))
        friend class mgdFunc;

    public:
        literalExpr(const node& n);

    public:
        using super::run;
        str run(const ucontainable& args) override;
        const wtype& getEvalType() const override;
        str& getStr();
        const str& getStr() const;

    private:
        str _str;
    };

    /*WRD_VERIFY(
     * if _str.type is immutable, _str should not bind any object.
     */
}
