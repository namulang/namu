#pragma once

#include "../expr.hpp"

namespace namu {

    class _nout getGenericExpr : public getExpr {
        NAMU(CLASS(getGenericExpr, getExpr, expr::exprType))

    public:
        getGenericExpr(const std::string orgName, const args& a): super(orgName, a) {}
        getGenericExpr(const node& from, const std::string orgName, const args& a):
            super(from, orgName, a) {}

    public:
        str run(const args& a) override {
            // TODO:
            return str();
        }
    };
}
