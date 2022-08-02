#include "blockExpr.hpp"
#include "../../frame/thread.hpp"
#include "../../loader/interpreter/verification.inl"
#include "../../loader/interpreter/tverification.hpp"
#include "../../builtin/primitive/wVoid.hpp"
#include "../../loader/interpreter/verifier.hpp"
#include "../../frame/frameInteract.hpp"

namespace namu {
    WRD_DEF_ME(blockExpr)

    void me::_inFrame(const bicontainable& args) {
        WRD_DI("%s._onInFrame()", getType().getName().c_str());

        frame& fr = namu::thread::get()._getNowFrame();
        if(nul(fr)) {
            WRD_E("fr == null");
            return;
        }

        fr.pushLocal(new scope());
    }

    void me::_outFrame() {
        WRD_DI("%s._onOutFrame()", getType().getName().c_str());

        frame& fr = namu::thread::get()._getNowFrame();
        if(nul(fr)) {
            WRD_E("fr == null");
            return;
        }

        fr.popLocal();
    }

    str me::run(const ucontainable& args) {
        frameInteract f1(*this); {
            str ret;
            frame& fr = namu::thread::get()._getNowFrame();
            for(auto& e : _exprs) {
                ret = e.run();
                if(fr.isReturned()) break;
            }
            return ret;
        }
    }

    const node& me::getEval() const {
        wcnt len = _exprs.len();
        if(len <= 0) return nulOf<node>();

        return _exprs[len-1].getEval();
    }



    WRD_VERIFY(blockExpr, visitSubNodes, { // visit sub nodes.
        WRD_DI("verify: blockExpr: visit sub nodes[%d]", it._exprs.len());

        frameInteract f1(it); {
            for(auto& e : it._exprs)
                verify(e);

            WRD_DI("verify: last stmt should match to ret type");

            const narr& stmts = it.getStmts();
            if(nul(stmts) || stmts.len() <= 0) return; // will be catched to another verification.

            const func& f = thread::get().getNowFrame().getFunc();
            if (nul(f)) return;

            const wtype& retType = f.getRet().getType();
            const node& lastStmt = *stmts.last();
            if(!lastStmt.isSub<returnExpr>() && retType == ttype<wVoid>::get()) {
                WRD_DI("implicit return won't verify when retType is void.");
                return;
            }
            const node& lastEval = lastStmt.getEval();
            if(nul(lastEval)) return _err(lastStmt.getPos(), NO_RET_TYPE);
            const wtype& lastType = lastEval.getType(); // to get type of expr, always uses evalType.
            if(nul(lastType)) return _err(lastStmt.getPos(), NO_RET_TYPE);
            if(!lastType.isSub(retType)) return _err(lastStmt.getPos(), errCode::RET_TYPE_NOT_MATCH, lastType.getName().c_str(),
                    retType.getName().c_str());

            WRD_DI("block.outFrame()\n");
        }
    })
}
