#pragma once

#include "../expr.hpp"

namespace wrd {

    class literalExpr : public expr {
        WRD(CLASS(literalExpr, expr, expr::exprType))
        friend class mgdFunc;

    public:
        literalExpr(const node& n): _str(n) {}

    public:
        using super::run;
        str run(const ucontainable& args) override {
            return _str;
        }

        const wtype& getEvalType() const override {
            // _str always binds to some object.
            return _str->getType();
        }

        str& getStr() { return _str; }
        const str& getStr() const { return _str; }

    private:
        str _str;
    };

    /*WRD_VERIFY(
     * if _str.type is immutable, _str should not bind any object.
     */
}
