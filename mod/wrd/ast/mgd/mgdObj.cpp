#include "mgdObj.hpp"

namespace wrd {

    WRD_DEF_ME(mgdObj)

    me& me::_assign(const me& rhs) {
        _owns = rhs._owns->deepClone();
        _subs.bind(_makeNewSubs());
        _org = rhs._org;

        return *this;
    }
}
