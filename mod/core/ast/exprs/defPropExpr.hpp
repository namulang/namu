#pragma once

#include "../expr.hpp"
#include "../param.hpp"
#include "../scope.hpp"

namespace namu {

    class visitor;

    class _nout defPropExpr : public expr {
        NAMU(CLASS(defPropExpr, expr, expr::exprType), VISIT())
        friend class mgdFunc;
        friend class verifier;

    public:
        defPropExpr(const std::string& name, const node& org);
        defPropExpr(const std::string& name, const node& org, const scope& where);

    public:
        using super::run;
        str run(const args& a) override;

        void setOrigin(const node& newOrg);
        const node& getOrigin() const;

        const std::string& getName() const;

        /// @return null of scope if this variable will be defined to local scope.
        const scope& getWhere() const;
        void setWhere(const scope& new1);

        str getEval() const override;

    private:
        str _org;
        std::string _name;
        tstr<scope> _where;
    };
}
