#include "returnExpr.hpp"
#include "../../builtin/primitive/wVoid.hpp"
#include "../../frame/thread.hpp"
#include "../../loader/interpreter/tverification.hpp"

namespace wrd {

    WRD_DEF_ME(returnExpr)

    me::returnExpr(): _ret(wVoid::singletone()) {}

    str me::run(const containable& args) {
        str ret = _ret ? _ret->run(args) : wVoid::singletone();

        thread::get()._getNowFrame().pushReturn(ret);
        return ret;
    }

    const wtype& me::getEvalType() const {
        if(!_ret)
            return ttype<wVoid>::get();

        return (const wtype&) _ret->getType(); // I guarrantee that it's wtype.
    }


    WRD_VERIFY({ // checks evalType of func is matched to me
        const func& f = thread::get().getNowFrame().getFunc();
        if(nul(f)) return _err(23);

        WRD_DI("verify: returnExpr: checks return[%s] == func[%s]", it.getEvalType().getName().c_str(),
            f.getEvalType().getName().c_str());

        if(!it.getType().isImpli(f.getEvalType()))
            return _err(24, it.getEvalType().getName().c_str(), f.getEvalType().getName().c_str());
    })
}
