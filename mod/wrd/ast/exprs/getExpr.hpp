#pragma once

#include "../ref.hpp"
#include "../expr.hpp"

namespace wrd {

    class getExpr : public expr {
        WRD(CLASS(getExpr, expr, expr::exprType))

    public:
        getExpr(const node& from, const std::string& name, const params& p = params())
            : _from(from), _name(name), _params(p) {}

    public:
        using super::run;
        str run(const containable& args) override {
            // believe that this expression was checked to be valid.
            str me = _from->as<node>();
            if(!me) return WRD_E("_from as node == null"), str();

            return str(me->sub(_name, _params));
        }

        const wtype& getEvalType() const override;
        const node& getFrom() const { return *_from; }
        const std::string& getName() const override { return _name; }
        const params& getParams() const override { return _params; }

    private:
        str _from;
        std::string _name;
        params _params;
    };
}
