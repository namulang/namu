#pragma once

#include "../expr.hpp"
#include "../params.hpp"

namespace namu {

    class _nout getExpr : public expr {
        NAMU(CLASS(getExpr, expr, expr::exprType),
            FRIEND_VERIFY(getExpr, isRunnable))

    public:
        getExpr(const std::string& name): _name(name) {}
        getExpr(const std::string& name, const args& a): _name(name), _args(a) {}
        getExpr(const node& from, const std::string& name): _from(from), _name(name) {}
        getExpr(const node& from, const std::string& name, const args& a): _from(from), _name(name), _args(a) {}

    public:
        using super::run;
        str run(const args& a) override;
        const node& getEval() const override;
        const node& getFrom() const;
        const std::string& getSubName() const;
        void setFrom(const node& newFrom) { _from.bind(newFrom); }

        /// @return nullable
        const args& getSubArgs() const;

    private:
        node& _get() const;

    private:
        str _from;
        std::string _name;
        tstr<args> _args;
    };
}
