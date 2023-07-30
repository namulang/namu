#include "nextExpr.hpp"
#include "../../frame/thread.hpp"
#include "../../visitor/visitor.hpp"

namespace namu {

    NAMU(DEF_ME(nextExpr), DEF_VISIT())

    me::nextExpr(const node& ret): super(ret) {}
    me::nextExpr() {}

    const retState& me::_onGetRetState() const {
        return frame::BLK_NEXT;
    }
}
