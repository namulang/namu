#pragma once

#include "../expr.hpp"

namespace wrd {

    class getExpr : public expr {
        WRD(CLASS(getExpr, expr, expr::exprType),
            FRIEND_VERIFY(getExpr, isRunnable))

    public:
        getExpr(const signature& sig): _sig(sig) {}
        getExpr(const node& from, const signature& sig): _from(from), _sig(sig) {}

    public:
        using super::run;
        str run(const ucontainable& args) override {
            // believe that this expression was checked to be valid.
            return str(_get());
        }

        const wtype& getEvalType() const override;
        const node& getFrom() const;
        const signature& getSubSignature() const { return _sig; }

    private:
        const node& _get() const {
            const node& from = getFrom();
            if(nul(from))
                return WRD_E("from == null"), nulOf<node>();

            return getFrom().sub(_sig);
        }

    private:
        str _from;
        signature _sig;
    };
}
