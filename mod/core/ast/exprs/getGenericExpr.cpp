#include "getGenericExpr.hpp"

#include "../../worker/visitor/visitor.hpp"
#include "../genericOrigin.hpp"
#include "../node.inl"

namespace nm {

    NM(DEF_ME(getGenericExpr), DEF_VISIT())

    me::getGenericExpr(const std::string& genericName, const args& typeParams):
        super(genericName, typeParams) {}

    me::getGenericExpr(const node& me, const std::string& genericName, const args& typeParams):
        super(me, genericName, typeParams) {}

    node& me::_onGet(node& me) const {
        const args& typs = getArgs();
        const std::string& name = getName();
        WHEN(nul(typs) || !typs.len()).err("_args.len() == 0").retNul<genericOrigin>();
        NM_DI("_name=%s, _args[%d]", getName(), typs.len());

        node &generic = me TO(template sub<genericOrigin>(name)) orRet NM_E("generic == null"),
             nulOf<node>();

        return *generic.run(getArgs());
    }
}
