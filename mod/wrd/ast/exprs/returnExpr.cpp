#include "returnExpr.hpp"
#include "../../builtin/primitive/wVoid.hpp"
#include "../../frame/thread.hpp"
#include "../../loader/interpreter/tverification.hpp"

namespace wrd {

    WRD_DEF_ME(returnExpr)

    me::returnExpr(): _ret(wVoid::singletone()) {}

    str me::run(const containable& args) {
        str ret = _ret ? _ret->run(args) : wVoid::singletone();

        const frame& fr = thread::get().getStackFrame().getCurrentFrame();
        fr.pushReturn(ret);
        return ret;
    }

    WRD_VERIFY({ // checks evalType of func is matched to me
        const func& f = thread::get().getStackFrame().getCurrentFrame().getFunc();
        if(nul(f)) return _err(23);

        if(!it.getEvalType().isImpli(f.getEvalType()))
            return _err(24, it.getEvalType().getName().c_str(), f.getEvalType().getName().c_str());
    })
}
