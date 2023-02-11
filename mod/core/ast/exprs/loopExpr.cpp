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
            fr.relRet();
            return true;
        }

        if(state == frame::BLK_NEXT) {
            fr.relRet();
            return false;
        }

        return false;
    }
}
