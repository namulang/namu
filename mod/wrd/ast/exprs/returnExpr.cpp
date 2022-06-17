#include "returnExpr.hpp"
#include "../../builtin/primitive/wVoid.hpp"
#include "../../frame/thread.hpp"
#include "../../loader/interpreter/tverification.hpp"
#include "../../loader/interpreter/verification.inl"
#include "../../loader/interpreter/verifier.hpp"

namespace wrd {

    WRD_DEF_ME(returnExpr)

    me::returnExpr(const node& ret): _ret(ret) {}
    me::returnExpr(): _ret(wVoid::singletone()) {}

    str me::run(const ucontainable& args) {
        str ret = _decideRet(args);
        thread::get()._getNowFrame().pushReturn(ret);
        return ret;
    }

    node& me::getRet() { return *_ret; }

    str me::_decideRet(const ucontainable& args) {
        if(!_ret) return str(wVoid::singletone());
        if(_ret->isSub<baseObj>()) return _ret; // case: obj

        return _ret->run(args); // case: expr
    }

    wbool me::canRun(const ucontainable& args) const {
        if(_ret)
            return _ret->canRun(args);
        return super::canRun(args);
    }

    const wtype& me::getEvalType() const {
        if(!_ret)
            return ttype<wVoid>::get();

        return (const wtype&) _ret->getEvalType(); // I guarrantee that it's wtype.
    }


    WRD_VERIFY({
        WRD_DI("verify: returnExpr: checks evalType of func is matched to me");

        const func& f = thread::get().getNowFrame().getFunc();
        if(nul(f)) return _srcErr(errCode::NO_FUNC_INFO);

        const wtype& itType = it.getEvalType();
        if(nul(itType)) return _srcErr(errCode::EXPR_EVAL_NULL);
        const wtype& fType = f.getRetType();
        WRD_DI("verify: returnExpr: checks return[%s] == func[%s]", itType.getName().c_str(),
            fType.getName().c_str());

        if(!itType.isImpli(fType))
            return _srcErr(errCode::RET_TYPE_NOT_MATCH, itType.getName().c_str(), fType.getName().c_str());
    })

    WRD_VERIFY({
        WRD_DI("verify: visit sub variable: _ret");

        verify(it.getRet());
    })
}
