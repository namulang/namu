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
        const wtype& type = it.getEvalType();
        WRD_DI("verify: expr: checks %s's evalType \"%s\" is valid", it.getType().getName().c_str(),
                (nul(type) ? "nul" : type.getName().c_str()));
        /* TODO: uncomment these.
        if(it.getPos().row < 1) return _err(1); // 1: this expr doesn't have row info.
        if(it.getPos().col < 1) return _err(6); // 6: this expr doesn't have col info.
        */
        if(nul(it.getEvalType())) return _err(2);
	})
}
