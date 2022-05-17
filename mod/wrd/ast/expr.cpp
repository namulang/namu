#include "expr.hpp"
#include "../builtin/container/native/tnmap.inl"
#include "../loader/interpreter/tverification.hpp"
#include "../loader/interpreter/verifier.hpp"

namespace wrd {

    WRD_DEF_ME(expr)

    nbicontainer& me::subs() {
        static nmap inner;
        return inner;
    }

    WRD_VERIFY({
#if WRD_IS_DBG
        const wtype& type = it.getEvalType();
        WRD_DI("verify: expr: checks %s's evalType \"%s\" is valid", it.getType().getName().c_str(),
                (nul(type) ? "nul" : type.getName().c_str()));
#endif
        /* TODO: uncomment these.
        if(it.getPos().row < 1) return _err(errCode::NO_ROW_INFO);
        if(it.getPos().col < 1) return _err(errCode::NO_COL_INFO);
        */
        if(nul(it.getEvalType())) return _err(errCode::EVAL_NULL_TYPE);
	})
}
