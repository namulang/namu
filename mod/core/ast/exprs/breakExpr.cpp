#include "breakExpr.hpp"

#include "../../frame/thread.hpp"
#include "../../worker/visitor/visitor.hpp"

namespace nm {

    NM(DEF_ME(breakExpr), DEF_VISIT())

    str me::getEval() const {
        static breakRet inner;
        return inner;
    }
}
