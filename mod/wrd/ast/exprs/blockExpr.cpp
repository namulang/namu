#include "blockExpr.hpp"
#include "../../frame/thread.hpp"

namespace wrd {
    WRD_DEF_ME(blockExpr)

    str me::run(const containable& args) {
        WRD_DI("%s._onInFrame()", getName().c_str());
        frame& fr = wrd::thread::get()._getStackFrame().getCurrentFrame();
        if(nul(fr))
            return WRD_E("fr == null"), str();
        fr.add(new narr());

        str ret;
        for(auto e=_exprs.begin<expr>(); e ; ++e)
            ret = e->run(nulOf<containable>());

        WRD_DI("%s._onOutFrame()", getName().c_str());
        fr.del();
        return ret;
    }
}
