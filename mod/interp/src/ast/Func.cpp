#include "Func.hpp"
#include "Obj.hpp"
#include "../frame/Thread.hpp"

namespace wrd {

    WRD_DEF_THIS(Func)

    Str This::run(NContainer& args) {
        StackFrame& sf = Thread::get()._getStackFrame();
        _onInStackFrame(sf, args);

        Str ret = _onRun(args);

        _onOutStackFrame(sf, args);
        return ret;
    }

    wbool This::_onInStackFrame(StackFrame& sf, NContainer& args) {
        Obj& me = args.head()->cast<Obj>();
        if(nul(me)) return WRD_E("args[0] wasn't Obj."), false;

        Frame* fr = new Frame();
        sf.add(fr);
        me._onInStackFrame(sf, args);
        fr->push(_shares);
        //TODO: fr->push(Parameter);
        return true;
    }

    wbool This::_onOutStackFrame(StackFrame& sf, NContainer& args) {
        Obj& me = args.head()->cast<Obj>();
        if(nul(me)) return WRD_E("args[0] wasn't Obj."), false;

        return sf.del();
    }

}
