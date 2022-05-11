#pragma once

#include "../expr.hpp"

namespace wrd {

    class runExpr : public expr {
        WRD(CLASS(runExpr, expr, expr::exprType))

    public:
        runExpr(const node& meObj, const std::string& name, const narr& args)
            : _me(meObj), _args(args), _name(name)  {}
        runExpr(const node& meObj, const narr& args): _me(meObj), _args(args) {}

    public:
        using super::run;
        str run(const ucontainable& args) override;

        const wtype& getEvalType() const override;

        node& getMe() { return *_me; }
        const node& getMe() const { return *_me; }
        void setMe(const node& newMe) {
            _me.bind(newMe);
        }

        const std::string& getName() const { return _name; }
        std::string& getName() { return _name; }

        narr& getArgs() { return _args; }
        const narr& getArgs() const { return _args; }

    private:
        str _me;
        narr _args;
        std::string _name;
    };
}
