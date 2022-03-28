#include "runExpr.hpp"
#include "../../loader/interpreter/tverification.hpp"
#include "../../loader/interpreter/verifier.hpp"
#include "../../thread/thread.hpp"

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

        return _me->getEvalType();
    }

    WRD_VERIFY({
        if(nul(it.getMe())) return _err(4); // 3: obj to be accessed was null.

        str me = it.getMe().as<node>();
        if(!me) return _err(4);

        str sub = me->sub(it.getName(), it.getArgs());
        if(!sub) return _err(3, me->getType().c_str(), it.getName().c_str());
        if(!sub->canRun(it.getArgs())) return _err(5); // 5: can't execute with this arguments
    })
}
