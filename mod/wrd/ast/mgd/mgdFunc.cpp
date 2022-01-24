#include "mgdFunc.hpp"
#include "../obj.hpp"
#include "../../builtin/container/native/tnarr.inl"
#include "../../builtin/container/native/tnchain.inl"
#include "../../frame/thread.hpp"

namespace wrd {

    WRD_DEF_ME(mgdFunc)

    str me::_onCast(narr& castedArgs) {
        frame& fr = thread::get()._getStackFrame().getCurrentFrame();
        if(nul(fr))
            return WRD_E("fr == null"), str();

        str ret;
        WRD_DI("%s._onInFrame()", getName().c_str());
        fr.pushLocal(subs());
        // TODO: put argument into new narr object.
        ret = _blk->run();

        WRD_DI("%s._onOutFrame()", getName().c_str());
        fr.popLocal();
        return ret;
    }
}
