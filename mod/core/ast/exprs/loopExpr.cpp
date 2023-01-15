#include "loopExpr.hpp"
#include "../../visitor/visitor.hpp"
#include "../../frame/thread.hpp"

namespace namu {

    NAMU(DEF_ME(loopExpr), DEF_VISIT())

    nbool me::_postProcess(frame& fr) const {
        const retState& state = fr.getRetState();
        if(state == frame::FUNC_RETURN)
            return true;

        if(state == frame::BLK_BREAK) {
            fr.setRet(frame::BLK_EMPTY);
            return true;
        }

        if(state == frame::BLK_NEXT) {
            fr.setRet(frame::BLK_EMPTY);
            return false;
        }

        return false;
    }
}
