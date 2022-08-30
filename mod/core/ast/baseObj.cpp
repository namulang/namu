#include "baseObj.hpp"
#include "func.hpp"
#include "../builtin/container/tucontainable.inl"
#include "../loader/interpreter/tverification.hpp"
#include "../frame/thread.hpp"
#include "../loader/interpreter/verifier.hpp"
#include "args.hpp"

namespace namu {

    NAMU(DEF_ME(baseObj))

    me::baseObj() {}

    str me::_onRunSub(node& sub, const args& a) {
        a.setMe(*this);
        return super::_onRunSub(sub, a);
    }

    str me::run(const args& a) {
        return str(this);
    }

    nbool me::canRun(const args& a) const {
        return a.len() <= 0;
    }

    void me::_inFrame(const bicontainable& args) {
        frames& frs = namu::thread::get()._getFrames();
        NAMU_DI("%s._inFrame()[%d]", getType().getName().c_str(), frs.len());

        frame& fr = *new frame();
        scope* s = new scope();
        s->add("me", *this);
        fr.pushLocal(s);
        fr.pushObj(*this);
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

        baseObj& prev = frame::_setMe(it);

        nmap tray;
        tray.add(func::ME, it);
        for(auto e = it.subs().begin(); e ;++e) {
            node& val = e.getVal();
            NAMU_DI("iteration [%s]=%s", e.getKey().c_str(), val.getType()
                    .getName().c_str());
            verify(val, tray);
            NAMU_DI("end of iteration [%s]=%s", e.getKey().c_str(), val.getType()
                    .getName().c_str());
        }

        frame::_setMe(prev);
    })
}
