#pragma once

#include "../expr.hpp"

namespace wrd {

    class getExpr : public expr {
        WRD(CLASS(getExpr, expr))

    public:
        getExpr(Ref* from, const std::string& name, narr* args = nullptr)
            : _from(from), _name(name), _args(args) {}

    public:
        str run(const containable& args) {
            // believe that this expression was checked to be valid.
            return str(_from->sub(_name, _args));
        }

        wbool isValid() const override {
            if(!super::isValid()) return false;
            if(!_from) return false;

            narr subs = _from->subAll(_name, _args);
            return subs.len() == 1;
        }

    private:
        tstr<Ref> _from;
        std::string _name;
        tstr<narr> _args;
    };
}
