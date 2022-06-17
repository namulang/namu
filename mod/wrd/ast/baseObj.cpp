#include "baseObj.hpp"
#include "func.hpp"
#include "../builtin/container/tucontainable.inl"
#include "../loader/interpreter/tverification.hpp"
#include "../frame/thread.hpp"
#include "../loader/interpreter/verifier.hpp"

namespace wrd {

    WRD_DEF_ME(baseObj)

    me::baseObj() {}

    str me::run(const ucontainable& args) {
        return str(this);
    }

    str me::_onRunSub(node& sub, const ucontainable& args) {
        _inFrame();
        str ret = super::_onRunSub(sub, args);
        _outFrame();
        return ret;
    }

    wbool me::canRun(const ucontainable& args) const {
        return args.len() <= 0;
    }

    void me::_inFrame() {
        frames& frs = wrd::thread::get()._getFrames();
        WRD_DI("%s._inFrame()[%d]", getType().getName().c_str(), frs.len());

        frame& fr = *new frame();
        scope* meScope = new scope();
        meScope->add("me", *this);
        fr.pushLocal(meScope);
        fr.setObj(*this);

        frs.add(fr);
    }

    void me::_outFrame() {
        frames& frs = wrd::thread::get()._getFrames();
        WRD_DI("%s._outFrame()[%d]", getType().getName().c_str(), frs.len()-1);

        frs.del();
    }

    WRD_VERIFY(baseObj, subNodes, {
        WRD_DI("verify: baseObj: %s iterateSubNodes. len=%d", it.getType().getName().c_str(), it.subs().len());

        it._inFrame();
        for(auto& p : it.subs())
            verify(p);
        it._outFrame();
    })
}
