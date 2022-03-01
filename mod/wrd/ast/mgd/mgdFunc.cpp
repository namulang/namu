#include "mgdFunc.hpp"
#include "../obj.hpp"
#include "../../builtin/container/native/tnarr.inl"
#include "../../builtin/container/native/tnchain.inl"
#include "../../frame/thread.hpp"

namespace wrd {

    WRD_DEF_ME(mgdFunc)

    str me::_onCastArgs(narr& castedArgs) {
        frame& fr = thread::get()._getStackFrame().getCurrentFrame();
        if(nul(fr))
            return WRD_E("fr == null"), str();

        str ret;
        WRD_DI("%s._onInFrame()", getName().c_str());
        fr.pushLocal(subs());
        fr.pushLocal(_nameArgs(castedArgs));
        // TODO: put argument into new narr object.
        ret = _blk->run();

        WRD_DI("%s._onOutFrame()", getName().c_str());
        fr.popLocal();
        return ret;
    }

    narr& me::_nameArgs(narr& args) {
        const params& params = getParams();
        if(args.len() != params.len())
            return WRD_E("length of args[%d] doesn't match to params[%d]", args.len(), params.len()),
                   args;

        for(int n=0; n < args.len(); n++)
            args[n].setName(params[n].getName());
        return args;
    }
}
