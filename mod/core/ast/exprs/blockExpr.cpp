#include "../../builtin/container/mgd/arr.hpp"
#include "blockExpr.hpp"
#include "../../frame/thread.hpp"
#include "../../builtin/primitive/nVoid.hpp"
#include "../../visitor/visitor.hpp"

namespace namu {
    NAMU(DEF_ME(blockExpr), DEF_VISIT())

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
        str ret;
        frame& fr = namu::thread::get()._getNowFrame();
        for(auto& e : _exprs) {
            ret = e.run();
            if(!fr.getRetState().isOverwritable(frame::BLK_EMPTY)) break;
        }

        fr.setRet(frame::BLK_RET, *ret);
        return ret;
    }

    str me::getEval() const {
        ncnt len = _exprs.len();
        if(len <= 0) return str();

        return _exprs[len-1].getEval();
    }
}
