#include "breakExpr.hpp"
#include "../../frame/thread.hpp"
#include "../../visitor/visitor.hpp"

namespace namu {

    NAMU(DEF_ME(breakExpr), DEF_VISIT())

    me::breakExpr(const node& ret): super(ret) {}
    me::breakExpr() {}

    const retState& me::_onGetRetState() const {
        return frame::BLK_BREAK;
    }
}
