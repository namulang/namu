#pragma once

#include "../expr.hpp"
#include "../../builtin/container/native/tnarr.hpp"

namespace namu {

    class _nout defArrayExpr : public expr {
        NAMU(CLASS(defArrayExpr, expr, expr::exprType), VISIT())

    public:
        defArrayExpr(const narr& elems): _elems(elems) {}
        defArrayExpr() {}

    public:
        using super::run;
        str run(const args& a) override;

        const node& getEval() const override;

        const narr& getElems() const;

    private:
        narr _elems;
    };
}
