#pragma once

#include "../expr.hpp"

namespace wrd {

    class runExpr : public expr {
        WRD(CLASS(runExpr, expr))

    public:
        runExpr(node* meObj, narr* args): _me(meObj), _args(args) {}

    public:
        str run(const containable& args) override {
            if(!_me) return WRD_E("_me == null"), str();

            return _me->

    private:
        str _me;
        scope _args;
    };
}
