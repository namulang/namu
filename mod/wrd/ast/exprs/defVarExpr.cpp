#include "defVarExpr.hpp"
#include "../../frame/thread.hpp"

namespace wrd {

    WRD_DEF_ME(defVarExpr)

    str me::_addFrame(node& new1) {
        if(thread::get()._getNowFrame().pushLocal(new1))
            return str(new1);
        return str();
    }
}
