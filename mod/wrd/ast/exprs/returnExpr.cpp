#include "returnExpr.hpp"
#include "../../builtin/primitive/wVoid.hpp"
#include "../../frame/thread.hpp"

namespace wrd {

    WRD_DEF_ME(returnExpr)

    me::returnExpr(): _ret(wVoid::singletone()) {}

    str me::run(const containable& args) {
        str ret = _ret ? _ret->run(args) : wVoid::singletone();

        const frame& fr = thread::get().getStackFrame().getCurrentFrame();
        fr.pushReturn(ret);
        return ret;
    }
}
