#pragma once

#include "../expr.hpp"
#include "../params.hpp"

namespace namu {

    class _wout getExpr : public expr {
        WRD(CLASS(getExpr, expr, expr::exprType),
            FRIEND_VERIFY(getExpr, isRunnable))

    public:
        getExpr(const std::string& name): _name(name) {}
        getExpr(const std::string& name, const narr& args): _name(name), _args(args) {}
        getExpr(const node& from, const std::string& name): _from(from), _name(name) {}
        getExpr(const node& from, const std::string& name, const narr& args): _from(from), _name(name), _args(args) {}

    public:
        using super::run;
        str run(const ucontainable& args) override;
        const node& getEval() const override;
        const node& getFrom() const;
        const std::string& getSubName() const;
        void setFrom(const node& newFrom) { _from.bind(newFrom); }

        /// @return nullable
        const narr& getSubArgs() const;

    private:
        node& _get() const;

    private:
        str _from;
        std::string _name;
        tstr<narr> _args;
    };
}
