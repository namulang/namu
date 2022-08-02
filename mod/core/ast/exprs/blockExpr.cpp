#include "blockExpr.hpp"
#include "../../frame/thread.hpp"
#include "../../loader/interpreter/verification.inl"
#include "../../loader/interpreter/tverification.hpp"
#include "../../builtin/primitive/nVoid.hpp"
#include "../../loader/interpreter/verifier.hpp"
#include "../../frame/frameInteract.hpp"

namespace namu {
    NAMU_DEF_ME(blockExpr)

    void me::_inFrame(const bicontainable& args) {
        NAMU_DI("%s._onInFrame()", getType().getName().c_str());

        frame& fr = namu::thread::get()._getNowFrame();
        if(nul(fr)) {
            NAMU_E("fr == null");
            return;
        }

        fr.pushLocal(new scope());
    }

    void me::_outFrame() {
        NAMU_DI("%s._onOutFrame()", getType().getName().c_str());

        frame& fr = namu::thread::get()._getNowFrame();
        if(nul(fr)) {
            NAMU_E("fr == null");
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
        ncnt len = _exprs.len();
        if(len <= 0) return nulOf<node>();

        return _exprs[len-1].getEval();
    }



    NAMU_VERIFY(blockExpr, visitSubNodes, { // visit sub nodes.
        NAMU_DI("verify: blockExpr: visit sub nodes[%d]", it._exprs.len());

        frameInteract f1(it); {
            for(auto& e : it._exprs)
                verify(e);

            NAMU_DI("verify: last stmt should match to ret type");

            const narr& stmts = it.getStmts();
            if(nul(stmts) || stmts.len() <= 0) return; // will be catched to another verification.

            const func& f = thread::get().getNowFrame().getFunc();
            if (nul(f)) return;

            const ntype& retType = f.getRet().getType();
            const node& lastStmt = *stmts.last();
            if(!lastStmt.isSub<returnExpr>() && retType == ttype<nVoid>::get()) {
                NAMU_DI("implicit return won't verify when retType is void.");
                return;
            }
            const node& lastEval = lastStmt.getEval();
            if(nul(lastEval)) return _err(lastStmt.getPos(), NO_RET_TYPE);
            const ntype& lastType = lastEval.getType(); // to get type of expr, always uses evalType.
            if(nul(lastType)) return _err(lastStmt.getPos(), NO_RET_TYPE);
            if(!lastType.isSub(retType)) return _err(lastStmt.getPos(), errCode::RET_TYPE_NOT_MATCH, lastType.getName().c_str(),
                    retType.getName().c_str());

            NAMU_DI("block.outFrame()\n");
        }
    })
}
