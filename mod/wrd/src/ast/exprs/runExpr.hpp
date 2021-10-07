#pragma once

#include "../expr.hpp"

namespace wrd {

    class runExpr : public expr {
        WRD(CLASS(runExpr, expr, expr::exprType))

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

            str me = _me->as<node>();
            if(!me) return nulOf<wtype>();

            return _me->getEvalType();
        }

        /* TODO: wbool isValid() const override {
           if(!super::isValid()) return false;
            if(!_me) return false;

            str me = _me->as<node>();
            if(!me) return false;

            return me->canRun(_args);
        }*/

        node& getMe() { return *_me; }
        const node& getMe() const { return *_me; }

        narr& getArgs() { return _args; }
        const narr& getArgs() const { return _args; }

    private:
        str _me;
        narr _args;
    };
}
