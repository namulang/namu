#include "blockExpr.hpp"
#include "../../frame/frame.hpp"

namespace wrd {

    WRD_DEF_ME(blockExpr)

    wbool me::_onInFrame(frame& fr, const ncontainer& args) {
        WRD_DI("%s._onInFrame()", getName().c_str());

        return fr.add(new narr());
    }

    wbool me::_onOutFrame(frame& fr, const ncontainer& args) {
        WRD_DI("%s._onOutFrame()", getName().c_str());

        fr.del();
        return true;
    }
}
