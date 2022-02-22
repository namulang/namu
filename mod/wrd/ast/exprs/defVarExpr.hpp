#pragma once

#include "../expr.hpp"
#include "../ref.hpp"

namespace wrd {

    class defVarExpr : public expr {
        WRD(CLASS(defVarExpr, expr, expr::exprType))
        friend class mgdFunc;

    public:
        defVarExpr(const ref& param): _param(param) {}

    public:
        using super::run;
        str run(const containable& args) override {
            const wtype& type = getEvalType();
            if(type.isImmutable()) {
                str ret = _addFrame(*type.makeAs<node>());
                ret->setName(_param.getName());
                return ret;
            }

            // mutable: _param may bind some object.
            return _addFrame(_param);
        }

        const wtype& getEvalType() const override {
            // I need to return static eval type:
            //  if I return _param->getType(), then actually it returns
            //  dynamic eval type.
            return _param.getType();
        }

        ref& getParam() { return _param; }
        const ref& getParam() const { return _param; }

    private:
        str _addFrame(node& new1);

    private:
        ref _param;
    };

    /*WRD_VERIFY(
     * if _param.type is immutable, _param should not bind any object.
     */
}
