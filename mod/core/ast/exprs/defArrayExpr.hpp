#pragma once

#include "../expr.hpp"
#include "../../builtin/container/native/tnarr.hpp"

namespace namu {

    class _nout defArrayExpr : public expr {
        NAMU(CLASS(defArrayExpr, expr, expr::exprType), VISIT())

    public:
        defArrayExpr(const node& type): _type(type) {}
        defArrayExpr(const narr& elems): _elems(elems) {}

    public:
        using super::run;
        str run(const args& a) override;

        const node& getEval() const override;

        const narr& getElems() const;

        const node& getArrayType() const;

    private:
        str _deduceElems() const;

    private:
        narr _elems;
        str _type;
    };
}
