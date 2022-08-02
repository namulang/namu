#include "baseObj.hpp"
#include "func.hpp"
#include "../builtin/container/tucontainable.inl"
#include "../loader/interpreter/tverification.hpp"
#include "../frame/thread.hpp"
#include "../loader/interpreter/verifier.hpp"

namespace namu {

    NAMU_DEF_ME(baseObj)

    me::baseObj() {}

    str me::_onRunSub(node& sub, const ucontainable& args) {
        baseObj& prev = frame::_setObj(*this);
        str ret = super::_onRunSub(sub, args);
        frame::_setObj(prev);

        return ret;
    }

    str me::run(const ucontainable& args) {
        return str(this);
    }

    nbool me::canRun(const ucontainable& args) const {
        return args.len() <= 0;
    }

    void me::_inFrame(const bicontainable& args) {
        frames& frs = namu::thread::get()._getFrames();
        NAMU_DI("%s._inFrame()[%d]", getType().getName().c_str(), frs.len());

        frame& fr = *new frame();
        scope* s = new scope();
        s->add("me", *this);
        fr.pushLocal(s);
        fr.pushObj(frame::getObj());
        frs.add(fr);
    }

    void me::_outFrame() {
        frames& frs = namu::thread::get()._getFrames();
        NAMU_DI("%s._outFrame()[%d]", getType().getName().c_str(), frs.len()-1);

        frs.del();
    }



    NAMU_VERIFY(baseObj, subNodes, {
        NAMU_DI("verify: baseObj: %s iterateSubNodes. len=%d", it.getType().getName().c_str(),
                it.subs().len());

        baseObj& prev = frame::_setObj(it);

        nmap tray;
        tray.add(func::ME, it);
        for(auto e = it.subs().begin(); e ;++e) {
            node& val = e.getVal();
            NAMU_DI("verify: baseObj: iterateSubNode[%s]=%s", e.getKey().c_str(), val.getType()
                    .getName().c_str());
            verify(val, tray);
        }

        frame::_setObj(prev);
    })
}
