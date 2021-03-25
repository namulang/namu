#include "Obj.hpp"
#include "../frame/StackFrame.hpp"

namespace wrd {

    WRD_DEF_THIS(Obj)

    wbool This::_onInStackFrame(StackFrame& sf, NContainer&) {
        Frame& fr = sf.getCurrentFrame();
        return fr.push(subs());
    }

    wbool This::_onOutStackFrame(StackFrame& sf, NContainer&) {
        return sf.getCurrentFrame().pop();
    }

}
