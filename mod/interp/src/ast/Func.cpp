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
        fr->push(subs());
        //TODO: fr->push(Parameter);
        return true;
    }

    wbool This::_onOutStackFrame(StackFrame& sf, NContainer& args) {
        Obj& me = args.head()->cast<Obj>();
        if(nul(me)) return WRD_E("args[0] wasn't Obj."), false;

        return sf.del();
    }

    const WTypes& This::getTypes() const {
        static WTypes inner;
        return inner;
    }

    wbool This::canRun(const WTypes& types) const {
        const WTypes& mine = getTypes();
        wcnt len = mine.size();
        if(types.size() != len) return false;

        for(int n=0; n < len ;n++) {
            const WType& it = *types[n];
            const WType& me = *mine[n];

            if(!it.isImpli(me)) return false;
        }

        return true;
    }
}
