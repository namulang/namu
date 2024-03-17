#include "retExpr.hpp"
#include "../../builtin/primitive/nVoid.hpp"
#include "../../frame/thread.hpp"
#include "../../visitor/visitor.hpp"

namespace namu {

    NAMU(DEF_ME(retExpr), DEF_VISIT())

    me::retExpr(const node& ret): _ret(ret) {}
    me::retExpr(): _ret(nVoid::singletone()) {}

    str me::run(const args& a) {
        if(!_ret) return str(nVoid::singletone());
        if(_ret->isSub<baseObj>()) return _ret; // case: obj

        str ret = _ret->as<node>(); // case: expr
        thread::get()._getNowFrame().setRet(frame::FUNC_RETURN, *ret);
        return ret;
    }

    node& me::getRet() {
        return *_ret;
    }

    me::priority me::prioritize(const args& a) const {
        if(_ret)
            return _ret->prioritize(a);
        return super::prioritize(a);
    }

    str me::getEval() const {
        if(!_ret)
            return _ret;

        return _ret->getEval();
    }
}
