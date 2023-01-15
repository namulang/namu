#include "whileExpr.hpp"
#include "../../visitor/visitor.hpp"
#include "../../frame/thread.hpp"

namespace namu {

    NAMU(DEF_ME(whileExpr), DEF_VISIT())

    me::whileExpr(const node& condition, const blockExpr& blk): super(blk), _condition(condition) {}

    str me::run(const args& a) {
        if(!_condition) return NAMU_E("_condition is null."), str();

        str res;
        frame& fr = thread::get()._getNowFrame();
        while(true) {
            str ased = _condition->asImpli<nBool>();
            if(!ased) return NAMU_E("cast to bool has been failed."), str();

            if(!ased->cast<nbool>())
                break;

            res = getBlock().run();
            if(_postProcess(fr))
                return res;
        }

        return res;
    }

    const node& me::getEval() const {
        return getBlock().getEval();
    }
}
