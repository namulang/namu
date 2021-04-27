#include "obj.hpp"
#include "../frame/stackFrame.hpp"

namespace wrd {

    WRD_DEF_ME(obj)

    wbool me::_onInFrame(frame& fr, ncontainer& args) {
        WRD_DI("%s._onInFrame()", getName().c_str());

        return fr.add(subs());
    }

    wbool me::_onOutFrame(frame& fr, ncontainer& args) {
        WRD_DI("%s._onOutFrame()", getName().c_str());

        return fr.del();
    }

}
