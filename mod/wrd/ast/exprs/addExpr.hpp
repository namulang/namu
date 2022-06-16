#pragma once

#include "../expr.hpp"
#include "../param.hpp"
#include "../../builtin/primitive/arithmeticObj.hpp"
#include "../scope.hpp"

namespace wrd {

    class _wout addExpr : public expr {
        WRD(CLASS(addExpr, expr, expr::exprType))

    public:
        addExpr(const node& lhs, const node& rhs): _lhs(str(lhs)), _rhs(str(rhs)) {}

    public:
        using super::run;
        str run(const ucontainable& args) override {
            if(!_lhs || !_rhs) return str();

            tstr<arithmeticObj> lhs(_lhs->run());
            tstr<arithmeticObj> rhs(_rhs->run());
            if(!lhs || !rhs) return str();

            return lhs->add(*rhs);
        }

        const wtype& getEvalType() const override;
        const node& getLeft() const { return *_lhs; }
        const node& getRight() const { return *_rhs; }

    private:
        str _lhs;
        str _rhs;
    };
}
