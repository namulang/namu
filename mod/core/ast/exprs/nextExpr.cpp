#include "nextExpr.hpp"
#include "../../frame/thread.hpp"
#include "../../visitor/visitor.hpp"

namespace namu {

    NAMU(DEF_ME(nextExpr), DEF_VISIT())

    const node& me::_onGetRet() const {
        static nextRet inner;
        return inner;
    }
}
