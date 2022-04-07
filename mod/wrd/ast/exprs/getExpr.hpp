#pragma once

#include "../expr.hpp"
#include "../params.hpp"

namespace wrd {

    class getExpr : public expr {
        WRD(CLASS(getExpr, expr, expr::exprType),
            FRIEND_VERIFY(getExpr, isRunnable))

    public:
        getExpr(const std::string& name): _name(name) {}
        getExpr(const std::string& name, const narr& args): _name(name), _args(args) {}
        getExpr(const node& from, const std::string& name): _from(from), _name(name) {}
        getExpr(const node& from, const std::string& name, const narr& args): _from(from), _name(name), _args(args) {}

    public:
        using super::run;
        str run(const ucontainable& args) override {
            // believe that this expression was checked to be valid.
            return str(_get());
        }

        const wtype& getEvalType() const override;
        const node& getFrom() const;
        const std::string& getSubName() const { return _name; }
        const narr& getSubArgs() const { return _args; }

    private:
        const node& _get() const {
            const node& from = getFrom();
            if(nul(from))
                return WRD_E("from == null"), nulOf<node>();

            return getFrom().sub(_name, _args);
        }

    private:
        str _from;
        std::string _name;
        narr _args;
    };
}
