#include "runExpr.hpp"
#include "../../loader/interpreter/tverification.hpp"
#include "../../loader/interpreter/verifier.hpp"
#include "../../frame/thread.hpp"

namespace wrd {

    WRD_DEF_ME(runExpr)

    str me::run(const ucontainable& args) {
        str me = _me->as<node>();
        if(!me) return WRD_E("_me as node == null"), str();

        return me->run(_name, _args);
    }

    const wtype& me::getEvalType() const {
        if(!_me) return nulOf<wtype>();

        str me = _me->as<node>();
        if(!me) return nulOf<wtype>();

        const func& f = _me->cast<func>();
        return nul(f) ? _me->getEvalType() : f.getRetType();
    }

    WRD_VERIFY({
        if(nul(it.getMe())) return _err(errCode::CANT_CAST_TO_NODE);

        str me = it.getMe().as<node>();
        if(!me) return _err(errCode::CANT_CAST_TO_NODE);

        str sub = me->sub(it.getName(), it.getArgs());
        if(!sub) return _err(errCode::NOT_EXIST, me->getType().getName().c_str(), it.getName().c_str());
        if(!sub->canRun(it.getArgs())) return _err(errCode::OBJ_WRONG_ARGS);
    })
}
