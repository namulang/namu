#pragma once

#include "../expr.hpp"
#include "../param.hpp"
#include "../scope.hpp"

namespace wrd {

    class _wout defVarExpr : public expr {
        WRD(CLASS(defVarExpr, expr, expr::exprType),
            FRIEND_VERIFY(defVarExpr, defineVariable))
        friend class mgdFunc;

    public:
        defVarExpr(const param& p): _param(p) {}
        defVarExpr(const param& p, const scope& where): _where(where), _param(p) {}

    public:
        using super::run;
        str run(const ucontainable& args) override;
        const param& getParam() const;
        /// @return null of scope if this variable will be defined to local scope.
        const scope& getWhere() const;
        void setWhere(const scope& new1);
        const wtype& getEvalType() const override;

    private:
        tstr<scope> _where;
        param _param;
    };
}
