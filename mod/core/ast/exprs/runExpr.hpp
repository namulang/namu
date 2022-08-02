#pragma once

#include "../expr.hpp"

namespace namu {

    class _nout runExpr : public expr {
        WRD(CLASS(runExpr, expr, expr::exprType))

    public:
        runExpr(const node& meObj, const std::string& name, const narr& args);
        runExpr(const node& meObj, const narr& args);

    public:
        using super::run;
        str run(const ucontainable& args) override;

        const node& getEval() const override;

        node& getMe();
        const node& getMe() const;
        void setMe(const node& newMe);

        const std::string& getName() const;
        std::string& getName();

        narr& getArgs();
        const narr& getArgs() const;

    private:
        str _me;
        narr _args;
        std::string _name;
    };
}
