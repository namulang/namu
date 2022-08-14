#pragma once

#include "getExpr.hpp"

namespace namu {

    class _nout getGenericExpr : public getExpr {
        NAMU(CLASS(getGenericExpr, getExpr, expr::exprType))

    public:
        getGenericExpr(const std::string& genericName, const args& typeParams):
                super(genericName, typeParams) {}
        getGenericExpr(const node& me, const std::string& genericName, const args& typeParams):
                super(me, genericName, typeParams) {}

    protected:
        str _get() const override {
            const args& typs = getSubArgs();
            const std::string& name = getSubName();
            if(nul(typs) || !typs.len()) return NAMU_E("_args.len() == 0"), str();
            NAMU_DI("_name=%s, _args[%d]", getSubName().c_str(), typs.len());

            str evalMe = getMe().isSub<expr>() ? getMe().as<node>() : getMe();
            if(!evalMe) return NAMU_E("from == null"), str();

            baseObj& generic = evalMe->sub<baseObj>(name);
            if(nul(generic)) return NAMU_E("generic == null"), str();

            return generic.run(typs);
        }
    };
}
