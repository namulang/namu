#include "getExpr.hpp"

namespace wrd {

    WRD_DEF_ME(getExpr)

    const wtype& me::getEvalType() const {
        wtypes typs = node::createTypesFromArgs(*_args);
        node& res = _from->sub(_name, *_args);
        if(nul(res)) return nulOf<wtype>();

        return res.getEvalType();
    }
}
