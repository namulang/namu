#include "returnExpr.hpp"
#include "../../builtin/primitive/nVoid.hpp"
#include "../../frame/thread.hpp"
#include "../../loader/interpreter/tverification.hpp"
#include "../../loader/interpreter/verification.inl"
#include "../../loader/interpreter/verifier.hpp"

namespace namu {

    NAMU_DEF_ME(returnExpr)

    me::returnExpr(const node& ret): _ret(ret) {}
    me::returnExpr(): _ret(nVoid::singletone()) {}

    str me::run(const args& a) {
        str ret = _decideRet(a);
        thread::get()._getNowFrame().pushReturn(ret);
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


    NAMU_VERIFY({
        NAMU_DI("verify: returnExpr: checks evalType of func is matched to me");

        const func& f = thread::get().getNowFrame().getFunc();
        if(nul(f)) return _srcErr(errCode::NO_FUNC_INFO);

        const node& itEval = it.getEval();
        if(nul(itEval)) return _srcErr(errCode::EXPR_EVAL_NULL);
        const ntype& itType = itEval.getType();
        if(nul(itType)) return _srcErr(errCode::EXPR_EVAL_NULL);
        const ntype& fType = f.getRet().getType();
        NAMU_DI("checks return[%s] == func[%s]", itType.getName().c_str(),
            fType.getName().c_str());

        if(!itType.isImpli(fType))
            return _srcErr(errCode::RET_TYPE_NOT_MATCH, itType.getName().c_str(), fType.getName().c_str());

        NAMU_DI("...verified: returnExpr: checks evalType of func is matched to me");
    })

    NAMU_VERIFY({
        NAMU_DI("verify: visit sub variable: _ret");

        verify(it.getRet());

        NAMU_DI("...verified: visit sub variable: _ret");
    })
}
