#include "mgdFunc.hpp"
#include "../obj.hpp"
#include "../../builtin/container/native/tnchain.inl"
#include "../../frame/thread.hpp"
#include "../../loader/interpreter/tverification.hpp"
#include "../params.hpp"

namespace wrd {

    WRD_DEF_ME(mgdFunc)

    str me::run(const ucontainable& args) {
        if(!_inFrame(*_evalArgs(args)))
            return str();

        str ret = _blk->run();
        _outFrame();
        return ret;
    }

    scope* me::_evalArgs(const ucontainable& args) {
        const params& ps = getParams();
        if(args.len() != ps.len())
            return WRD_E("length of args(%d) and typs(%d) doesn't match.", args.len(), ps.len()), nullptr;

        scope* ret = new scope();
        int n = 0;
        for(const node& e: args) {
            const param& p = ps[n++];
            str evaluated = e.as(p.getOrigin());
            if(!evaluated) return nullptr;

            ret->add(p.getName(), *evaluated);
        }
        return ret;
    }

    wbool me::_inFrame(scope& s) {
        frame& fr = thread::get()._getNowFrame();
        if(nul(fr)) return WRD_E("fr == null"), false;
        if(nul(s)) return WRD_E("s == null"), false;

        WRD_DI("%s._onInFrame()", getType().getName().c_str());
        fr.pushLocal(subs());
        fr.setFunc(*this);
        return fr.pushLocal(s);
    }

    void me::_outFrame() {
        frame& fr = thread::get()._getNowFrame();
        WRD_DI("%s._onOutFrame()", getType().getName().c_str());
        fr.setFunc(nulOf<func>());
        fr.popLocal();
        fr.popLocal();
    }

    WRD_VERIFY({
        const wtype& retType = it.getRetType();
        if(nul(retType)) return _err(errCode::NO_RET_TYPE);
        if(!retType.isSub(ttype<node>::get()))
            return _err(errCode::WRONG_RET_TYPE, retType.getName().c_str());

        const blockExpr& blk = it.getBlock();
        if(nul(blk) || blk.getStmts().len() <= 0)
            return _err(errCode::NO_STMT_IN_FUNC);
    })

    namespace {
        void _prepareArgsAlongParam(const params& ps, scope& s) {
            for(const auto& p : ps)
                s.add(p.getName(), *p.getOrigin());
        }
    }

    // TODO: verify arguments

    WRD_VERIFY(mgdFunc, subNodes, {
        WRD_DI("verify: mgdFunc: %s iterateBlock[%d]", it.getType().getName().c_str(), it._blk->subs().len());
        scope s;
        _prepareArgsAlongParam(it.getParams(), s);

        it._inFrame(s);
        verify(*it._blk);
        it._outFrame();
    })

    WRD_VERIFY({ // last stmt should match to ret type
        const narr& stmts = it.getBlock().getStmts();
        if(nul(stmts) || stmts.len() <= 0) return; // will be catched to another verification.

        const wtype& lastStmt = stmts.last()->getEvalType(); // to get type of expr, always uses evalType.
        const wtype& retType = it.getRetType();
        if(nul(lastStmt)) return _err(NO_RET_TYPE);
        if(!lastStmt.isSub(retType)) return _err(errCode::RET_TYPE_NOT_MATCH, lastStmt.getName().c_str(),
                retType.getName().c_str());
    })
}
