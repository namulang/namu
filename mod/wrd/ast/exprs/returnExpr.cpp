#include "returnExpr.hpp"
#include "../../builtin/primitive/wVoid.hpp"
#include "../../frame/thread.hpp"
#include "../../loader/interpreter/tverification.hpp"

namespace wrd {

    WRD_DEF_ME(returnExpr)

    me::returnExpr(): _ret(wVoid::singletone()) {}

    str me::run(const ucontainable& args) {
        str ret = _ret ? _ret->run(args) : wVoid::singletone();

        thread::get()._getNowFrame().pushReturn(ret);
        return ret;
    }

    const wtype& me::getEvalType() const {
        if(!_ret)
            return ttype<wVoid>::get();

        return (const wtype&) _ret->getEvalType(); // I guarrantee that it's wtype.
    }


    WRD_VERIFY({
        WRD_DI("verify: returnExpr: checks evalType of func is matched to me");

        const func& f = thread::get().getNowFrame().getFunc();
        if(nul(f)) return _err(errCode::NO_FUNC_INFO);

        const wtype& itType = it.getEvalType();
        if(nul(itType)) return _err(errCode::EXPR_EVAL_NULL);
        const wtype& fType = f.getRetType();
        WRD_DI("verify: returnExpr: checks return[%s] == func[%s]", itType.getName().c_str(),
            fType.getName().c_str());

        if(!itType.isImpli(fType))
            return _err(errCode::RET_TYPE_NOT_MATCH, itType.getName().c_str(), fType.getName().c_str());
    })
}
