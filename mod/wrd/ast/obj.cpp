#include "obj.hpp"
#include "func.hpp"
#include "../builtin/container/uucontainable.inl"
#include "../loader/interpreter/tverification.hpp"
#include "../frame/thread.hpp"

namespace wrd {

    WRD_DEF_ME(obj)

    me::obj() {}
    me::obj(const signature& sig): _sig(sig) {}
    me::obj(const signature& sig, const nchain& subs): _sig(sig), _subs(subs) {}

    str me::run(const ucontainable& args) {
        func& fun = getCtors().get<func>([&args](const func& candidate) {
            return candidate.canRun(args);
        });

        if(nul(fun))
            return WRD_E("%s object isn't constructable with given args", getType().getName().c_str()), str();

        return fun.run(args);
    }

    str me::_onRunSub(node& sub, const ucontainable& args) {
        if(!sub.doesNeedScope())
            return super::_onRunSub(sub, args);

        _inFrame();
        str ret = super::_onRunSub(sub, args);
        _outFrame();
        return ret;
    }

    wbool me::canRun(const ucontainable& args) const {
        wcnt n = getCtors().getAll<func>([&args](const func& f) {
            return f.canRun(args);
        }).len();

        switch(n) {
            case 0: return WRD_E("%s object isn't constructible with given args.", getType().getName().c_str()), false;
            case 1: return true;
        }

        return WRD_E("%s object have %d ctors. it's ambigious.", getType().getName().c_str(), n), false;
    }

    void me::_inFrame() {
        WRD_DI("%s._inFrame()", getName().c_str());

        frame& fr = *new frame();
        fr.setObj(subs());
        wrd::thread::get()._getFrames().add(fr);
    }

    void me::_outFrame() {
        WRD_DI("%s._outFrame()", getName().c_str());

        wrd::thread::get()._getFrames().del();
    }

    WRD_VERIFY(obj, subNodes, {
        WRD_DI("verify: obj: %s[type=%s] iterateSubNodes[%d]", it.getName().c_str(), it.getType().getName().c_str(),
            it.subs().len());

        for(auto& sub : it.subs()) {
            if(!sub.doesNeedScope()) {
                verify(sub);
                continue;
            }

            it._inFrame();
            verify(sub);
            it._outFrame();
        }
    })
}
