#include "nextExpr.hpp"
#include "../../frame/thread.hpp"
#include "../../visitor/visitor.hpp"

namespace namu {

    NAMU(DEF_ME(nextExpr), DEF_VISIT())

    const retState& me::_onGetRetState() const {
        return frame::BLK_NEXT;
    }
}
