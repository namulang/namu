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

            str me = _me->as<node>();
            if(!me) return WRD_E("_me as node == null"), str();

            return str(me->run(*_args));
        }

    private:
        str _me;
        tstr<narr> _args;
    };
}
