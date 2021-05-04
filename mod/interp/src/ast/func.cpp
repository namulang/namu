#include "func.hpp"
#include "obj.hpp"
#include "../frame/frameInteract.hpp"
#include "../frame/thread.hpp"

namespace wrd {

    WRD_DEF_ME(func)

    str me::run(const ncontainer& args) {
        obj& meObj = args.begin()->cast<obj>();
        if(nul(meObj)) return WRD_E("args[0] wasn't obj."), str();

        stackFrame& fr = thread::get()._getStackFrame();
        fr.add(new frame());

        str ret;
        { frameInteract inter(meObj, args);
            { frameInteract inter(*this, args);
                //TODO: cast all of args and turns into nonconst new array.
                ret = _onRun((ncontainer&) args);
            }
        }

        fr.del();
        return ret;
    }

    wbool me::_onInFrame(frame& fr, const ncontainer& args) {
        WRD_DI("%s._onInFrame()", getName().c_str());

        fr.add(subs());
        return true;
    }

    wbool me::_onOutFrame(frame& fr, const ncontainer& args) {
        WRD_DI("%s._onOutFrame()", getName().c_str());

        return fr.del();
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
