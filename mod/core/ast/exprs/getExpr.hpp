#pragma once

#include "../expr.hpp"
#include "../params.hpp"

namespace namu {

    class visitor;

    class _nout getExpr : public expr {
        NAMU(CLASS(getExpr, expr, expr::exprType), VISIT())
        friend class verifier;

    public:
        getExpr(const std::string& name): _name(name) {}
        getExpr(const std::string& name, const args& a): _name(name), _args(a) {}
        getExpr(const node& me, const std::string& name): _me(me), _name(name) {}
        getExpr(const node& me, const std::string& name, const args& a): _me(me), _name(name), _args(a) {}

    public:
        using super::run;
        str run(const args& a) override;
        const node& getEval() const override;
        const node& getMe() const;
        const std::string& getSubName() const;
        void setMe(const node& newMe) { _me.bind(newMe); }

        /// @return nullable
        const args& getSubArgs() const;

    protected:
        virtual str _get() const;

    private:
        str _me;
        std::string _name;
        tstr<args> _args;
    };
}
