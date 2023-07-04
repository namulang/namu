#include "getGenericExpr.hpp"
#include "../../visitor/visitor.hpp"
#include "../node.inl"
#include "../genericObj.hpp"

namespace namu {

    NAMU(DEF_ME(getGenericExpr), DEF_VISIT())

    str me::_get(nbool evalMode) const {
        genericObj& generic = _getGenericObj();
        if(nul(generic)) return NAMU_E("generic == null"), str();

        return generic.run(getSubArgs());
    }

    genericObj& me::_getGenericObj() const {
        const args& typs = getSubArgs();
        const std::string& name = getSubName();
        if(nul(typs) || !typs.len()) return NAMU_E("_args.len() == 0"), nulOf<genericObj>();
        NAMU_DI("_name=%s, _args[%d]", getSubName().c_str(), typs.len());

        str evalMe = getMe().isSub<expr>() ? getMe().as<node>() : getMe();
        if(!evalMe) return NAMU_E("from == null"), nulOf<genericObj>();

        return evalMe->sub<genericObj>(name);
    }
}
