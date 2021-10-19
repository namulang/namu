#include "getExpr.hpp"
#include "../../loader/interpreter/tverification.hpp"
#include "../../loader/interpreter/verifier.hpp"
#include "../ast/node.inl"
#include "../ast/func.hpp"

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

    WRD_VERIFY(getExpr, {
        if(nul(it.getFrom())) return _err<err>(3); // 3: obj to be accessed was null.

        // TODO: I have to check that the evalType has what matched to given _types.
        // Until then, I rather use as() func and it makes slow emmersively.
        if(nul(it.getEvalType())) return _err<err>(2); // 2: evaludated as nulled type.
        return true;
    })

    str me::run(const containable& args) {
        // TODO: args validness check.

        // find 'main' func:
        func& fun = _root->sub<func>("main"); // TODO: support generic type of str[]
        if(nul(fun))
            return WRD_E("there is no 'main' func."), str();

        thread* prev = *_get();
        *_get() = this;
        str res = fun.run(args);
        *_get() = prev;

        return res;
    }
}
