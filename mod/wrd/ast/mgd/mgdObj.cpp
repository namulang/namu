#include "mgdObj.hpp"

namespace wrd {

    WRD_DEF_ME(mgdObj)

    me& me::_assign(const me& rhs) {
        _owns = rhs._owns->deepClone();
        _subs.bind(_makeNewSubs());
        _org = rhs._org;

        return *this;
    }

    wbool me::_onInFrame(frame& fr, const containable& args) {
        WRD_DI("%s._onInFrame()", getName().c_str());

        return fr.add(*nchain::wrapDeep(subs()));
    }

    wbool me::_onOutFrame(frame& fr, const containable& args) {
        WRD_DI("%s._onOutFrame()", getName().c_str());

        fr.del();
        return true;
    }
}
