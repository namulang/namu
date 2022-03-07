#include "mgdFunc.hpp"
#include "../obj.hpp"
#include "../../builtin/container/native/tnarr.inl"
#include "../../builtin/container/native/tnchain.inl"
#include "../../frame/thread.hpp"
#include "../../loader/interpreter/tverification.hpp"

namespace wrd {

    WRD_DEF_ME(mgdFunc)

    str me::_onCastArgs(narr& args) {
        if(!_inLocalFrame(args))
            return str();

        str ret = _blk->run();
        _outLocalFrame();
        return ret;
    }

    wbool me::_inLocalFrame(narr& args) {
        frame& fr = thread::get()._getStackFrame().getCurrentFrame();
        if(nul(fr))
            return WRD_E("fr == null"), false;

        WRD_DI("%s._onInFrame()", getName().c_str());
        fr.pushLocal(subs());
        fr.pushLocal(_nameArgs(args));
        // TODO: put argument into new narr object.

        WRD_DI("%s._onOutFrame()", getName().c_str());
        fr.popLocal();
        return true;
    }

    void me::_outLocalFrame() {
        frame& fr = thread::get()._getStackFrame().getCurrentFrame();
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

    WRD_VERIFY(mgdFunc, {
        const wtype& eval = it.getEvalType();
        if(nul(eval)) return _err(21);
        if(!eval.isSub(ttype<node>::get())) return _err(20, eval.getName().c_str());

        const blockExpr& blk = it.getBlock();
        if(nul(blk) || blk.subs().len() <= 0) return _err(22);

        return true;
    })
}
