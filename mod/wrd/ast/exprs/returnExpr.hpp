#pragma once

#include "../expr.hpp"

namespace wrd {

    class returnExpr : public expr {
        WRD(CLASS(returnExpr, expr, expr::exprType))

    public:
        returnExpr(const node& ret): _ret(ret) {}
        returnExpr();

    public:
        using super::run;
        str run(const containable& args) override;

        wbool canRun(const containable& args) const override {
            if(_ret)
                return _ret->canRun(args);
            return super::canRun(args);
        }

        const wtype& getEvalType() const override;

    private:
        str _ret;
    };
}
