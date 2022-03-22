#include "expr.hpp"
#include "../builtin/container/native/tnarr.inl"
#include "../loader/interpreter/tverification.hpp"
#include "../loader/interpreter/verifier.hpp"

namespace wrd {

    WRD_DEF_ME(expr)

    nucontainer& me::subs() {
        static narr inner;
        return inner;
    }

    WRD_VERIFY({
        /* TODO: uncomment these.
        if(it.getPos().row < 1) return _err(1); // 1: this expr doesn't have row info.
        if(it.getPos().col < 1) return _err(6); // 6: this expr doesn't have col info.
        */
        if(nul(it.getEvalType())) return _err(2);
	})
}
