#include "getExpr.hpp"
#include "../../loader/interpreter/tverification.hpp"
#include "../../loader/interpreter/verifier.hpp"
#include "../node.inl"

namespace wrd {

    WRD_DEF_ME(getExpr)

    const wtype& me::getEvalType() const {
        str me = _from->as<node>();
        if(!me) return nulOf<wtype>();

        narr res = _from->subAll(_name, _params);
        if(res.len() != 1) return nulOf<wtype>();

        // I don't return it as getEvalType() here. getExpr is a previous step before evaluation.
        return res[0].getType();
    }

    WRD_VERIFY({
        if(nul(it.getFrom())) return _err(3); // 3: obj to be accessed was null.

        // TODO: I have to check that the evalType has what matched to given _params.
        // Until then, I rather use as() func and it makes slow emmersively.
        if(nul(it.getEvalType())) return _err(2); // 2: evaludated as nulled type.
    })
}
