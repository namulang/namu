#include "obj.hpp"
#include "../frame/stackFrame.hpp"

namespace wrd {

    WRD_DEF_ME(obj)

    wbool me::_onInStackFrame(stackFrame& sf, ncontainer&) {
        frame& fr = sf.getCurrentFrame();
        return fr.push(subs());
    }

    wbool me::_onOutStackFrame(stackFrame& sf, ncontainer&) {
        return sf.getCurrentFrame().pop();
    }

}
