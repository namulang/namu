#include "blockExpr.hpp"
#include "../../frame/thread.hpp"
#include "../../loader/interpreter/tverification.hpp"

namespace wrd {
    WRD_DEF_ME(blockExpr)

    wbool me::_inFrame() {
        WRD_DI("%s._onInFrame()", getType().getName().c_str());

        frame& fr = wrd::thread::get()._getNowFrame();
        if(nul(fr))
            return WRD_E("fr == null"), false;

        fr.pushLocal(new scope());
        return true;
    }

    void me::_outFrame() {
        WRD_DI("%s._onOutFrame()", getType().getName().c_str());

        frame& fr = wrd::thread::get()._getNowFrame();
        fr.popLocal();
    }

    str me::run(const ucontainable& args) {
        if(!_inFrame())
            return str();

        str ret;
        frame& fr = wrd::thread::get()._getNowFrame();
        for(auto& e : _exprs) {
            ret = e.run();
            if(fr.isReturned()) break;
        }

        _outFrame();
        return ret;
    }

    WRD_VERIFY(blockExpr, visitSubNodes, { // visit sub nodes.
        WRD_DI("verify: blockExpr: visit sub nodes[%d]", it._exprs.len());
        if(!it._inFrame()) return _err(errCode::BLK_CANT_MAKE_FRAME);

        for(auto& e : it._exprs)
            verify(e);

        it._outFrame();
    })
}
