#include "getExpr.hpp"

namespace wrd {

    WRD_DEF_ME(getExpr)

    const wtype& me::getEvalType() const {
        narr res = _from->subAll(_name, *_args);
        if(res.len() != 1) return nulOf<wtype>();

        return res[0].getEvalType();
    }
}
