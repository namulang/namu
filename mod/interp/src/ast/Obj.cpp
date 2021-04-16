#include "Obj.hpp"
#include "../frame/StackFrame.hpp"

namespace wrd {

    WRD_DEF_ME(Obj)

    wbool me::_onInStackFrame(StackFrame& sf, NContainer&) {
        Frame& fr = sf.getCurrentFrame();
        return fr.push(subs());
    }

    wbool me::_onOutStackFrame(StackFrame& sf, NContainer&) {
        return sf.getCurrentFrame().pop();
    }

}
