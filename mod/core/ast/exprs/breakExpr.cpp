#include "breakExpr.hpp"
#include "../../frame/thread.hpp"
#include "../../visitor/visitor.hpp"

namespace namu {

    NAMU(DEF_ME(breakExpr), DEF_VISIT())

    const node& me::_onGetRet() const {
        static breakRet inner;
        return inner;
    }
}
