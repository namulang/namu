#include "mgdObj.hpp"
#include "../../frame/stackFrame.hpp"

namespace wrd {

    WRD_DEF_ME(mgdObj)

    me& me::_assign(const me& rhs) {
        _shares = rhs._shares;
        _subs.bind(*rhs.subs().deepClone());
        _subs->link(*_shares);

        return *this;
    }

    wbool me::_onInFrame(frame& fr, const ncontainer& args) {
        WRD_DI("%s._onInFrame()", getName().c_str());

        return fr.add(subs());
    }

    wbool me::_onOutFrame(frame& fr, const ncontainer& args) {
        WRD_DI("%s._onOutFrame()", getName().c_str());

        return fr.del();
    }
}
