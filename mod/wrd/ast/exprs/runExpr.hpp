#pragma once

#include "../expr.hpp"

namespace wrd {

    class runExpr : public expr {
        WRD(CLASS(runExpr, expr, expr::exprType))

    public:
        runExpr(const node& meObj, const std::string& name, const narr& args)
            : _me(meObj), _name(name), _args(args) {}

    public:
        using super::run;
        str run(const ucontainable& args) override;

        const wtype& getEvalType() const override {
            if(!_me) return nulOf<wtype>();

            str me = _me->as<node>();
            if(!me) return nulOf<wtype>();

            return _me->getEvalType();
        }

        node& getMe() { return *_me; }
        const node& getMe() const { return *_me; }

        const std::string& getName() const { return _name; }
        std::string& getName() { return _name; }

        narr& getArgs() { return _args; }
        const narr& getArgs() const { return _args; }

    private:
        str _me;
        std::string _name;
        narr _args;
    };
}
