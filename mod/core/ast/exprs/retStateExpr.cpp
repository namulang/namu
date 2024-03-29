#include "retStateExpr.hpp"
#include "../../frame/thread.hpp"
#include "../../visitor/visitor.hpp"

namespace namu {

    NAMU(DEF_ME(retStateExpr), DEF_VISIT())

    str me::run(const args& a) {
        thread::get()._getNowFrame().setRet(_onGetRet());
        return _onGetRet();
    }

    str me::getEval() const {
        return _onGetRet();
    }

    priority me::prioritize(const args& a) const {
        return NO_MATCH;
    }
}
