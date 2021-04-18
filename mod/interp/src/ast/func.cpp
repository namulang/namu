#include "func.hpp"
#include "obj.hpp"
#include "../frame/thread.hpp"

namespace wrd {

    WRD_DEF_ME(func)

    str me::run(ncontainer& args) {
        stackFrame& sf = thread::get()._getStackFrame();
        _onInStackFrame(sf, args);

        str ret = _onRun(args);

        _onOutStackFrame(sf, args);
        return ret;
    }

    wbool me::_onInStackFrame(stackFrame& sf, ncontainer& args) {
        obj& me = args.head()->cast<obj>();
        if(nul(me)) return WRD_E("args[0] wasn't obj."), false;

        frame* fr = new frame();
        sf.add(fr);
        me._onInStackFrame(sf, args);
        fr->push(subs());
        //TODO: fr->push(Parameter);
        return true;
    }

    wbool me::_onOutStackFrame(stackFrame& sf, ncontainer& args) {
        obj& me = args.head()->cast<obj>();
        if(nul(me)) return WRD_E("args[0] wasn't obj."), false;

        return sf.del();
    }

    const wtypes& me::getTypes() const {
        static wtypes inner;
        return inner;
    }

    wbool me::canRun(const wtypes& types) const {
        const wtypes& mine = getTypes();
        wcnt len = mine.size();
        if(types.size() != len) return false;

        for(int n=0; n < len ;n++) {
            const wtype& it = *types[n];
            const wtype& me = *mine[n];

            if(!it.isImpli(me)) return false;
        }

        return true;
    }
}
