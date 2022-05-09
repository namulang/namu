#include "getExpr.hpp"
#include "../../loader/interpreter/tverification.hpp"
#include "../../loader/interpreter/verifier.hpp"
#include "../../frame/thread.hpp"
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

    WRD_VERIFY(getExpr, isRunnable, {
        // TODO: I have to check that the evalType has what matched to given _params.
        // Until then, I rather use as() func and it makes slow emmersively.
        if(nul(it.getEvalType())) return _err(errCode::EVAL_NULL_TYPE);
        const node& got = it._get();
        if(nul(got)) {
            const node& from = it.getFrom();
            return _err(errCode::NOT_EXIST, from.getType().getName().c_str(), it._name.c_str());

        WRD_DI("verify: getExpr: isRunnable: got=%s, it=%s", got.getType().getName().c_str(),
                it.getType().getName().c_str());
        }
    })
}
