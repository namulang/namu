#include "baseObj.hpp"
#include "func.hpp"
#include "../builtin/container/tucontainable.inl"
#include "../loader/interpreter/tverification.hpp"
#include "../frame/thread.hpp"
#include "../loader/interpreter/verifier.hpp"

namespace wrd {

    WRD_DEF_ME(baseObj)

    me::baseObj() {}

    str me::_onRunSub(node& sub, const ucontainable& args) {
        frames& frs = wrd::thread::get()._getFrames();
        frame& fr = *new frame();
        fr.setObj(*this);
        frs.add(fr);

        return super::_onRunSub(sub, args);
    }

    str me::run(const ucontainable& args) {
        return str(this);
    }

    wbool me::canRun(const ucontainable& args) const {
        return args.len() <= 0;
    }

    void me::_inFrame(const bicontainable& args) {
        WRD_DI("%s._inFrame()", getType().getName().c_str());

        frame& fr = wrd::thread::get()._getNowFrame();
        fr.applyObjScope();
        scope* s = new scope();
        s->add("me", *this);
        fr.pushLocal(s);
    }

    void me::_outFrame() {
        frames& frs = wrd::thread::get()._getFrames();
        WRD_DI("%s._outFrame()[%d]", getType().getName().c_str(), frs.len()-1);

        frs.del();
    }



    WRD_VERIFY(baseObj, subNodes, {
        WRD_DI("verify: baseObj: %s iterateSubNodes. len=%d", it.getType().getName().c_str(), it.subs().len());

        nmap tray;
        tray.add(func::ME, it);
        for(auto& p : it.subs())
            verify(p, tray);
    })
}
