#pragma once

#include "../expr.hpp"

namespace namu {

    class _nout getGenericExpr : public expr {
        NAMU(CLASS(getGenericExpr, expr, expr::exprType))

    public:
        getGenericExpr(const std::string orgName, const std::vector<std::string>& paramNames) {
        }

    public:
        str run(const args& a) override {
            // TODO:
            return str();
        }
    };
}
