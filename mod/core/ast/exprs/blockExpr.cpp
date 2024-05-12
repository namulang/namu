#include "../../builtin/container/mgd/arr.hpp"
#include "blockExpr.hpp"
#include "../../frame/thread.hpp"
#include "../../builtin/primitive/nVoid.hpp"
#include "../../visitor/visitor.hpp"
#include "retStateExpr.hpp"

namespace namu {

    NAMU(DEF_ME(blockExpr), DEF_VISIT())

    me::blockExpr() {}

    const narr& me::getStmts() const {
        return _exprs;
    }

    narr& me::getStmts() {
        return _exprs;
    }

    clonable* me::deepClone() const {
        NAMU_DW("blockExpr: deepClone");

        me* ret = (me*) clone();
        ret->_exprs.rel();
        for(auto e=_exprs.begin(); e ;e++)
            ret->_exprs.add((node*) e->deepClone());

        return ret;
    }

    void me::inFrame(const bicontainable& args) {
        NAMU_DI("%s._onInFrame()", getType().getName().c_str());

        frame& fr = namu::thread::get()._getNowFrame();
        if(nul(fr)) {
            NAMU_E("fr == null");
            return;
        }

        fr.pushLocal(new scope());
    }

    void me::outFrame() {
        NAMU_DI("%s._onOutFrame()", getType().getName().c_str());

        frame& fr = namu::thread::get()._getNowFrame();
        if(nul(fr)) {
            NAMU_E("fr == null");
            return;
        }

        fr.popLocal();
    }

    str me::run(const args& a) {
        // for optimization, blockExpr's frame should be controlled from outside of this this.
        // that's why I didn't use frameInteracter here. see forExpr::run().
        str ret;

        const auto& ex = thread::get().getEx();
        nidx exN = ex.len() - 1; // blockExpr will judge exception occurs when exN is changed to after running one of its stmt.
        for(auto& e : _exprs) {
            ret = e.as<node>(); // if e is expr, it runs(). if not, it returns itself.
            if(ex.len() > exN) {
                _onOccurEx(ex, exN);
                return ret; // this might be err instance.
                            // so it's not the return type of what the func told, but it's okay.
                            // all derived err object can be assigned to any type.
            }
            if(ret && ret->isSub<retState>()) break;
        }
        return ret;
    }

    void me::_onOccurEx(const errReport& ex, nidx after) {
        NAMU_E("oops, exception occurs:\n");
        for(nidx n=after; n < ex.len() ;n++) {
            const err& e = ex[n];
            e.dump();
        }
    }

    str me::getEval() const {
        if(_exprs.isEmpty()) return str();
        return _exprs.last()->getEval();
    }
}
