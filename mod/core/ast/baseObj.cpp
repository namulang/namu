#include "../builtin/container/mgd/arr.hpp"
#include "baseObj.hpp"
#include "baseFunc.hpp"
#include "../builtin/container/tucontainable.inl"
#include "../frame/thread.hpp"
#include "args.hpp"
#include "baseFunc.hpp"
#include "node.inl"

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

    me::priority me::prioritize(const args& a) const {
        priority min = node::NO_MATCH; // beginning from the worst value.
        tnarr<prior<baseFunc>> subs = subAll<baseFunc>(baseObj::CTOR_NAME, a);
        for(const auto& sub : subs)
            min = min < sub.lv ? min : sub.lv;
        return min;
    }

    void me::inFrame(const bicontainable& args) {
        frames& frs = namu::thread::get()._getFrames();
        NAMU_DI("%s.inFrame()[%d]", getType().getName().c_str(), frs.len());

        frame& fr = *new frame();
        scope* s = new scope();
        s->add("me", *this);
        fr.pushLocal(s);
        fr.pushObj(*this);
        frs.add(fr);
    }

    void me::outFrame() {
        frames& frs = namu::thread::get()._getFrames();
        NAMU_DI("%s._outFrame()[%d]", getType().getName().c_str(), frs.len()-1);

        frs.del();
    }
}
