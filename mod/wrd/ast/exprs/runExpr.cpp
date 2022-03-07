#include "runExpr.hpp"
#include "../../loader/interpreter/tverification.hpp"
#include "../../loader/interpreter/verifier.hpp"

namespace wrd {

    WRD_DEF_ME(runExpr)

    WRD_VERIFY({
        if(nul(it.getMe())) return _err(3); // 3: obj to be accessed was null.

        str me = it.getMe().as<node>();
        if(!me) return _err(4);
        if(!me->canRun(it.getArgs())) return _err(5); // 5: can't execute with this arguments

        return true;
    })
}
