#pragma once

#include "../expr.hpp"
#include "../params.hpp"

namespace wrd {

    class _wout makeExpr : public expr {
        WRD(CLASS(makeExpr, expr, expr::exprType))

    public:
        makeExpr(const node& from): _from(from) {}

    public:
        using super::run;
        str run(const ucontainable& args) override {
            tstr<obj> out(_from->run());
            if(!out) return str();

            return str(out->getOrigin().clone());
        }
        const wtype& getEvalType() const override {
            return _from->getEvalType();
        }
        const node& getFrom() const {
            return *_from;
        }

    private:
        str _from;
    };
}
