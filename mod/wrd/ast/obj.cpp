#include "obj.hpp"
#include "func.hpp"
#include "../builtin/container/tucontainable.inl"
#include "../loader/interpreter/tverification.hpp"
#include "../frame/thread.hpp"
#include "../loader/interpreter/verifier.hpp"

namespace wrd {

    WRD_DEF_ME(obj)

    me::obj() {}

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
        WRD_DI("%s._inFrame()", getType().getName().c_str());

        frame& fr = *new frame();
        scope* meScope = new scope();
        meScope->add("me", *this);
        fr.pushLocal(meScope);
        fr.setObj(*this);

        wrd::thread::get()._getFrames().add(fr);
    }

    void me::_outFrame() {
        WRD_DI("%s._outFrame()", getType().getName().c_str());

        wrd::thread::get()._getFrames().del();
    }

    WRD_VERIFY(obj, subNodes, {
        WRD_DI("verify: obj: %s iterateSubNodes[%d]", it.getType().getName().c_str(), it.subs().len());

        it._inFrame();
        for(auto& p : it.subs())
            verify(p);
        it._outFrame();
    })
}
