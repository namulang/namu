#pragma once

#include "../expr.hpp"

namespace wrd {

    class getExpr : public expr {
        WRD(CLASS(getExpr, expr, expr::exprType))

    public:
        getExpr(const node& from, const std::string& name, const wtypes& args = wtypes())
            : _from(from), _name(name), _types(args) {}

    public:
        using super::run;
        str run(const containable& args) override {
            // believe that this expression was checked to be valid.
            str me = _from->as<node>();
            if(!me) return WRD_E("_from as node == null"), str();

            return str(me->sub(_name, _types));
        }

        const wtype& getEvalType() const override;
        const node& getFrom() const { return *_from; }
        const std::string& getName() const override { return _name; }
        const wtypes& getParams() const override { return _types; }

    private:
        str _from;
        std::string _name;
        wtypes _types;
    };
}
