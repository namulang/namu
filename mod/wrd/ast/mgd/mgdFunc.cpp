#include "mgdFunc.hpp"
#include "../obj.hpp"
#include "../../builtin/container/native/tnarr.inl"
#include "../../builtin/container/native/tnchain.inl"
#include "../../frame/frameInteract.hpp"
#include "../../frame/thread.hpp"

namespace wrd {

    WRD_DEF_ME(mgdFunc)

    wbool me::_onInFrame(frame& fr, const containable& args) {
        WRD_DI("%s._onInFrame()", getName().c_str());

        fr.add(subs());
        return true;
    }

    wbool me::_onOutFrame(frame& fr, const containable& args) {
        WRD_DI("%s._onOutFrame()", getName().c_str());

        fr.del();
        return true;
    }

    str me::_onCast(narr& castedArgs) {
        stackFrame& sf = thread::get()._getStackFrame();
        sf.add(new frame());

        str ret;
        frameInteract inter(*this, castedArgs); {
            ret = _blk->run(castedArgs);
        }

        sf.del();
        return ret;
    }
}
