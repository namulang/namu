#include "obj.hpp"
#include "func.hpp"
#include "../builtin/container/tucontainable.inl"
#include "../loader/interpreter/tverification.hpp"
#include "../frame/thread.hpp"

namespace wrd {

    WRD_DEF_ME(obj)

    me::obj() {}
    me::obj(const scopes& subs): _subs(subs) {}

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

    funcs& me::getCtors() {
        static funcs inner;
        return inner;
    }

    void me::_inFrame() {
        WRD_DI("%s._inFrame()", getType().getName().c_str());

        frame& fr = *new frame();
        fr.setObj(*this);
        wrd::thread::get()._getFrames().add(fr);
    }

    void me::_outFrame() {
        WRD_DI("%s._outFrame()", getType().getName().c_str());

        wrd::thread::get()._getFrames().del();
    }

    WRD_VERIFY(obj, subNodes, {
        WRD_DI("verify: obj: %s iterateSubNodes[%d]", it.getType().getName().c_str(), it.subs().len());

        for(auto& p : it.subs()) {
            node& val = p.getVal();
            if(!val.doesNeedScope()) {
                verify(val);
                continue;
            }

            it._inFrame();
            verify(val);
            it._outFrame();
        }
    })
}
