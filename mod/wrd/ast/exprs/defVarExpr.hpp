#pragma once

#include "../expr.hpp"
#include "../param.hpp"

namespace wrd {

    class defVarExpr : public expr {
        WRD(CLASS(defVarExpr, expr, expr::exprType))
        friend class mgdFunc;

    public:
        defVarExpr(const param& p): _param(p) {}

    public:
        using super::run;
        str run(const ucontainable& args) override {
            return _addFrame(_param);
        }

        const param& getParam() const { return _param; }

        const wtype& getEvalType() const override {
            // I need to return static eval type:
            //  if I return _param->getType(), then actually it returns
            //  dynamic eval type.
            return _param.getType();
        }

    private:
        str _addFrame(param& p) const;

    private:
        param _param;
    };

    /*WRD_VERIFY(
     * if _param.type is immutable, _param should not bind any object.
     */
}
