#pragma once

#include "../expr.hpp"
#include "../param.hpp"
#include "../scope.hpp"

namespace wrd {

    class _wout akaExpr : public expr {
        WRD(CLASS(akaExpr, expr, expr::exprType))
        friend class mgdFunc;
        typedef scopes::iter iter;

    public:
        akaExpr(const node& from, const std::string& name): _from(from), _name(name) {}

    public:
        using super::run;
        str run(const ucontainable& args) override {
            if(!_from || _name.empty()) return WRD_E("_from not exist"), str();

            const node& from = _from->as<node>();
            if(nul(from))
                return WRD_E("from is null"), str();

            thread::get()._getNowFrame().

            return from;
        }

        const wtype& getEvalType() const override { return _from->getEvalType(); }
        const node& getFrom() const { return *_from; }
        const std::string& getSubName() const { return _name; }
        /// @return null of scope if this variable will be defined to local scope.
        const scope& getWhere() const;
        void setWhere(const scope& new1);

    private:
        str _from;
        std::string _name;
        tstr<scope> _where;
    };
}
