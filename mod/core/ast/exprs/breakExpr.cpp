#include "breakExpr.hpp"
#include "../../frame/thread.hpp"
#include "../../visitor/visitor.hpp"

namespace namu {

    NAMU(DEF_ME(breakExpr), DEF_VISIT())

    const retState& me::onGetRetState() const {
        return frame::BLK_BREAK;
    }
}
