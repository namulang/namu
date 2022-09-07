#include "baseObj.hpp"
#include "func.hpp"
#include "../builtin/container/tucontainable.inl"
#include "../frame/thread.hpp"
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
}
