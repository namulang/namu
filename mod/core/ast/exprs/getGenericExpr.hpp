#pragma once

#include "getExpr.hpp"

namespace namu {

    class visitor;
    class genericObj;

    class _nout getGenericExpr : public getExpr {
        NAMU(CLASS(getGenericExpr, getExpr, expr::exprType), VISIT())
        friend class verifier;

    public:
        getGenericExpr(const std::string& genericName, const args& typeParams):
                super(genericName, typeParams) {}
        getGenericExpr(const node& me, const std::string& genericName, const args& typeParams):
                super(me, genericName, typeParams) {}

    protected:
        genericObj& _getGenericObj() const;

    protected:
        str _get() const override;
    };
}
