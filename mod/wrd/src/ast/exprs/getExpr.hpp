#pragma once

#include "../expr.hpp"
#include "../ref.hpp"

namespace wrd {

    class getExpr : public expr {
        WRD(CLASS(getExpr, expr))

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

        wbool isValid() const override {
            if(!super::isValid()) return false;
            if(!_from) return false;

            return !nul(getEvalType());
        }

    private:
        str _from;
        std::string _name;
        wtypes _types;
    };
}
