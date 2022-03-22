#include "blockExpr.hpp"
#include "../../frame/thread.hpp"
#include "../../loader/interpreter/tverification.hpp"

namespace wrd {
    WRD_DEF_ME(blockExpr)

    wbool me::_inFrame() {
        WRD_DI("%s._onInFrame()", getName().c_str());

        frame& fr = wrd::thread::get()._getNowFrame();
        if(nul(fr))
            return WRD_E("fr == null"), false;

        fr.pushLocal(new narr());
        return true;
    }

    void me::_outFrame() {
        WRD_DI("%s._onOutFrame()", getName().c_str());

        frame& fr = wrd::thread::get()._getNowFrame();
        fr.popLocal();
    }

    str me::run(const ucontainable& args) {
        if(!_inFrame())
            return str();

        str ret;
        frame& fr = wrd::thread::get()._getNowFrame();
        for(auto e=_exprs.begin<expr>(); e ; ++e) {
            ret = e->run(nulOf<ucontainable>());
            if(fr.isReturned()) break;
        }

        _outFrame();
        return ret;
    }

    WRD_VERIFY(blockExpr, visitSubNodes, { // visit sub nodes.
        WRD_DI("verify: blockExpr: visit sub nodes[%d]", it.subs().len());
        if(!it._inFrame()) return _err(25);

        for(node& e : it.subs())
            verify(e);

        it._outFrame();
    })
}
