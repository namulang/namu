#include "mgdFunc.hpp"
#include "../obj.hpp"
#include "../../frame/frameInteract.hpp"
#include "../../frame/thread.hpp"

namespace wrd {

    WRD_DEF_ME(mgdFunc)

    wbool me::_onInFrame(frame& fr, const ncontainer& args) {
        WRD_DI("%s._onInFrame()", getName().c_str());

        fr.add(subs());
        return true;
    }

    wbool me::_onOutFrame(frame& fr, const ncontainer& args) {
        WRD_DI("%s._onOutFrame()", getName().c_str());

        return fr.del();
    }

    str me::_onCast(narr& castedArgs) {
        obj& meObj = castedArgs[0].cast<obj>();
        stackFrame& fr = thread::get()._getStackFrame();
        fr.add(new frame());

        str ret;
        { frameInteract inter(meObj, castedArgs);
            { frameInteract inter(*this, castedArgs);
                ret = _onRun(castedArgs);
            }
        }

        fr.del();
        return ret;
    }
}
