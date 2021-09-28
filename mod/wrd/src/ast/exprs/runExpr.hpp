#pragma once

#include "../expr.hpp"

namespace wrd {

    class runExpr : public expr {
        WRD(CLASS(runExpr, expr))

    public:
        runExpr(const node& meObj, const narr& args): _me(meObj), _args(args) {}

    public:
        using super::run;
        str run(const containable& args) override {
            if(!_me) return WRD_E("_me == null"), str();

            str me = _me->as<node>();
            if(!me) return WRD_E("_me as node == null"), str();

            return str(me->run(_args));
        }

        const wtype& getEvalType() const override {
            if(!_me) return nulOf<wtype>();

            return _me->getEvalType();
        }

        wbool isValid() const override {
            if(!super::isValid()) return false;
            if(!_me) return false;

            return _me->canRun(_args);
        }

    private:
        str _me;
        narr _args;
    };
}
