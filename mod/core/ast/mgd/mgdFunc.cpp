#include "mgdFunc.hpp"
#include "../obj.hpp"
#include "../../builtin/container/native/tnchain.inl"
#include "../../frame/thread.hpp"
#include "../params.hpp"
#include "../../loader/interpreter/tverification.hpp"
#include "../../loader/interpreter/verification.inl"
#include "../../loader/interpreter/verifier.hpp"
#include "../../frame/frameInteract.hpp"

namespace namu {

    NAMU_DEF_ME(mgdFunc)

    me::mgdFunc(const params& ps, const node& retType):
            super(), _params(ps), _retType(retType), _blk(new blockExpr()) {}
    me::mgdFunc(const params& ps, const node* retType):
            super(), _params(ps), _retType(retType), _blk(new blockExpr()) {}
    me::mgdFunc(const params& ps, const node& retType, const blockExpr& newBlock):
            super(), _params(ps), _retType(retType), _blk(newBlock) {}
    me::mgdFunc(const params& ps, const node* retType, const blockExpr& newBlock):
            super(), _params(ps), _retType(retType), _blk(newBlock) {}

    blockExpr& me::getBlock() { return *_blk; }
    const blockExpr& me::getBlock() const { return *_blk; }
    const node& me::getRet() const { return *_retType; }
    nbicontainer& me::subs() { return _shares; }
    const params& me::getParams() const { return _params; }

    str me::run(const args& a) {
        str ret;
        if(nul(a)) return NAMU_E("a == null"), ret;

        // s is from heap space. but freed by _outFrame() of this class.
        scope& s = *_evalArgs(a);
        baseObj& meObj = a.getMe();
        if(nul(meObj)) return NAMU_E("meObj == null"), ret;

        frameInteract f1(meObj); {
            frameInteract f2(*this, s); {
                _blk->run();
                ret = thread::get()._getNowFrame().popReturn();
            }
        }
        return ret;
    }

    scope* me::_evalArgs(const ucontainable& args) {
        const params& ps = getParams();
        if(args.len() != ps.len())
            return NAMU_E("length of args(%d) and typs(%d) doesn't match.", args.len(), ps.len()), nullptr;

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

    void me::_inFrame(const bicontainable& args) {
        frame& fr = thread::get()._getNowFrame();
        if(nul(fr)) {
            NAMU_E("fr == null");
            return;
        }

        NAMU_DI("%s._onInFrame()", getType().getName().c_str());
        fr.pushLocal(subs());
        fr.setFunc(*this);
        fr.pushLocal((nbicontainer&) args); // including 'me'
    }

    void me::_outFrame() {
        NAMU_DI("%s._onOutFrame()", getType().getName().c_str());

        frame& fr = thread::get()._getNowFrame();
        // TODO: is it safe to delete below lines?
        fr.setFunc(nulOf<func>());
        fr.popLocal();
        fr.popLocal();
    }



    NAMU_VERIFY({
        NAMU_DI("verify: retType exists and stmts exist one at least");

        const node& retType = it.getRet();
        if(nul(retType)) return _srcErr(errCode::NO_RET_TYPE);
        if(!retType.isSub(ttype<node>::get()))
            return _srcErr(errCode::WRONG_RET_TYPE, retType.getType().getName().c_str());

        const blockExpr& blk = it.getBlock();
        if(nul(blk) || blk.getStmts().len() <= 0)
            return _err(blk.getPos(), errCode::NO_STMT_IN_FUNC);
    })

    namespace {
        void _prepareArgsAlongParam(const params& ps, scope& s) {
            for(const auto& p : ps)
                s.add(p.getName(), p.getOrigin());
        }
    }

    // TODO: verify arguments

    NAMU_VERIFY(mgdFunc, subNodes, {
        NAMU_DI("verify: mgdFunc: %s iterateBlock[%d]", it.getType().getName().c_str(), it._blk->subs().len());
        scope* s = new scope();
        _prepareArgsAlongParam(it.getParams(), *s);

        baseObj& meObj = frame::_getMe();
        if(nul(meObj)) return _srcErr(errCode::FUNC_REDIRECTED_OBJ);

        frameInteract f1(meObj); {
            frameInteract f2(it, *s); {
                verify(*it._blk);
            }
        }
    })
}
