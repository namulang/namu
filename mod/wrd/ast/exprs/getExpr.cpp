#include "getExpr.hpp"
#include "../../loader/interpreter/tverification.hpp"
#include "../../loader/interpreter/verifier.hpp"
#include "../node.inl"

namespace wrd {

    WRD_DEF_ME(getExpr)

    const node& me::getFrom() const {
        if(!_from)
            return thread::get().getNowFrame();
        return *_from;
    }

    const wtype& me::getEvalType() const {
        const node& got = _get();
        if(nul(got))
            return nulOf<wtype>();
        return got.getEvalType();
    }

    WRD_VERIFY({
        // TODO: I have to check that the evalType has what matched to given _params.
        // Until then, I rather use as() func and it makes slow emmersively.
        if(nul(it.getEvalType())) return _err(2); // 2: evaludated as nulled type.
        const node& got = _get();
        if(nul(got)) {
            const node& from = getFrom();
            return _err(3, from.getType().getName().c_str(), from.getName().c_str(), _name.c_str());
    })
}
