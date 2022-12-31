#include "returnExpr.hpp"
#include "../../builtin/primitive/nVoid.hpp"
#include "../../frame/thread.hpp"
#include "../../visitor/visitor.hpp"

namespace namu {

    NAMU(DEF_ME(returnExpr), DEF_VISIT())

    me::returnExpr(const node& ret): _ret(ret) {}
    me::returnExpr(): _ret(nVoid::singletone()) {}

    str me::run(const args& a) {
        str ret = _decideRet(a);
        thread::get()._getNowFrame().setRet(frame::FUNC_RETURN, *ret);
        return ret;
    }

    node& me::getRet() { return *_ret; }

    str me::_decideRet(const args& a) {
        if(!_ret) return str(nVoid::singletone());
        if(_ret->isSub<baseObj>()) return _ret; // case: obj

        return _ret->run(a); // case: expr
    }

    nbool me::canRun(const args& a) const {
        if(_ret)
            return _ret->canRun(a);
        return super::canRun(a);
    }

    const node& me::getEval() const {
        if(!_ret)
            return nulOf<node>();

        return _ret->getEval();
    }
}
