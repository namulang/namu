#include "loopExpr.hpp"
#include "../../visitor/visitor.hpp"
#include "../../frame/thread.hpp"

namespace namu {

    NAMU(DEF_ME(loopExpr), DEF_VISIT())

    me::loopExpr(const blockExpr& blk): _blk(blk) {}

    blockExpr& me::getBlock() const {
        return *_blk;
    }

    str me::getEval() const {
        return _eval;
    }

    nbool me::setEval(const node& new1) const {
        return _eval.bind(new1);
    }

    nbool me::_postProcess(frame& fr) const {
        const retState& state = fr.getRetState();
        if(state == frame::FUNC_RETURN) return true;
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
