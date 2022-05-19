#include "blockExpr.hpp"
#include "../../frame/thread.hpp"
#include "../../loader/interpreter/tverification.hpp"
#include "../../builtin/primitive/wVoid.hpp"

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

        {
            WRD_DI("verify: last stmt should match to ret type");

            const narr& stmts = it.getStmts();
            if(nul(stmts) || stmts.len() <= 0) return; // will be catched to another verification.

            const func& f = thread::get().getNowFrame().getFunc();
            if (nul(f)) return;

            const wtype& retType = f.getRetType();
            const node& lastStmt = *stmts.last();
            if(!lastStmt.isSub<returnExpr>() && retType == ttype<wVoid>::get()) {
                WRD_DI("implicit return won't verify when retType is void.");
                return;
            }
            const wtype& lastType = lastStmt.getEvalType(); // to get type of expr, always uses evalType.
            if(nul(lastType)) return _err(NO_RET_TYPE);
            if(!lastType.isSub(retType)) return _err(errCode::RET_TYPE_NOT_MATCH, lastType.getName().c_str(),
                    retType.getName().c_str());
        }

        WRD_DI("block.outFrame()\n");
        it._outFrame();
    })
}
