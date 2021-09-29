#include "getExpr.hpp"

namespace wrd {

    WRD_DEF_ME(getExpr)

    const wtype& me::getEvalType() const {
        str me = _from->as<node>();
        if(!me) return nulOf<wtype>();

        narr res = _from->subAll(_name, _types);
        if(res.len() != 1) return nulOf<wtype>();

        // I don't return it as getEvalType() here. getExpr is a previous step before evaluation.
        return res[0].getType();
    }
}
