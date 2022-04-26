#include "defVarExpr.hpp"
#include "../../frame/thread.hpp"

namespace wrd {

    WRD_DEF_ME(defVarExpr)

    str me::_addFrame(param& p) const {
        if(thread::get()._getNowFrame().pushLocal(p.getName(), (node&) *p.getOrigin()))
            return str(p.getOrigin());
        return str();
    }
}
