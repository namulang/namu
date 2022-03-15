#pragma once

#include "../ref.hpp"
#include "../expr.hpp"

namespace wrd {

    class getExpr : public expr {
        WRD(CLASS(getExpr, expr, expr::exprType))

    public:
        getExpr(const std::string& name, const params& p = nulOf<params>())
            : _name(name), _params(p) {}
        getExpr(const node& from, const std::string& name, const params& p = nulOf<params>())
            : _from(from), _name(name), _params(p) {}

    public:
        using super::run;
        str run(const containable& args) override {
            // believe that this expression was checked to be valid.
            return str(_get());
        }

        const wtype& getEvalType() const override;
        const node& getFrom() const;
        const std::string& getName() const override { return _name; }
        const params& getParams() const override { return *_params; }

    private:
        const node& _get() {
            const node& from = getFrom();
            if(nul(from))
                return WRD_E("from == null"), nulOf<node>();

            const params& p = getParams();
            if(nul(p))
                return getFrom().sub(_name);
            return getFrom().sub(_name, p);
        }

    private:
        str _from;
        std::string _name;
        /// if params set to null, it means that this expr only finds variables from _from.
        params _params;
    };
}
