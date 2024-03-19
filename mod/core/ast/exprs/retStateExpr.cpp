#include "retStateExpr.hpp"
#include "../../builtin/primitive/nVoid.hpp"
#include "../../frame/thread.hpp"
#include "../../visitor/visitor.hpp"

namespace namu {

    NAMU(DEF_ME(retStateExpr), DEF_VISIT())

    me::retStateExpr(const node& ret): _ret(ret) {}
    me::retStateExpr(): _ret(nVoid::singletone()) {}

    str me::run(const args& a) {
        str ret = _decideRet(a);
        thread::get()._getNowFrame().setRet(_onGetRetState(), *ret);
        return ret;
    }

    node& me::getRet() {
        return *_ret;
    }

    str me::_decideRet(const args& a) {
        if(!_ret) return str(nVoid::singletone());
        if(_ret->isSub<baseObj>()) return _ret;

        return _ret->run(a);
    }

    priority me::prioritize(const args& a) const {
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
