#pragma once

#include "../expr.hpp"
#include "../../builtin/container/mgd/arr.hpp"

namespace namu {

    class _nout defArrayExpr : public expr {
        NAMU(CLASS(defArrayExpr, expr, expr::exprType), VISIT())

    public:
        defArrayExpr(const node& type): _type(type) {}
        defArrayExpr(const narr& elems): _elems(elems) {}

    public:
        using super::run;
        str run(const args& a) override;

        str getEval() const override;

        const node& getArrayType() const;

        const arr& getOrigin() const;

    private:
        str _deduceElems() const;

    private:
        str _type;
        narr _elems;
        mutable tstr<arr> _org;
    };
}
