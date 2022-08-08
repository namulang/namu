#pragma once

#include "../expr.hpp"
#include "../param.hpp"
#include "../scope.hpp"

namespace namu {

    class _nout defVarExpr : public expr {
        NAMU(CLASS(defVarExpr, expr, expr::exprType),
            FRIEND_VERIFY(defVarExpr, defineVariable))
        friend class mgdFunc;

    public:
        defVarExpr(const std::string& name, const node& org);
        defVarExpr(const std::string& name, const node& org, const scope& where);

    public:
        using super::run;
        str run(const args& a) override;
        const node& getOrigin() const;
        const std::string& getName() const;
        /// @return null of scope if this variable will be defined to local scope.
        const scope& getWhere() const;
        void setWhere(const scope& new1);
        const node& getEval() const override;

    private:
        str _org;
        std::string _name;
        tstr<scope> _where;
    };
}
