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
        for(auto& e : _exprs) {
            ret = e.as<node>(); // if e is expr, it runs(). if not, it returns itself.
            if(ret && ret->isSub<retState>()) break;
        }
        return ret;
    }

    str me::getEval() const {
        if(_exprs.isEmpty()) return str();
        return _exprs.last()->getEval();
    }
}
