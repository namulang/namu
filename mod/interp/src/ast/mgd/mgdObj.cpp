#include "mgdObj.hpp"

namespace wrd {

    WRD_DEF_ME(mgdObj)

    me& me::_assign(const me& rhs) {
        _shares = rhs._shares;
        _subs.bind(*rhs.subs().deepClone());
        _subs->link(*_shares);
        _org = rhs._org;

        return *this;
    }
}
