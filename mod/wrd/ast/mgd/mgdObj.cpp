#include "mgdObj.hpp"

namespace wrd {

    WRD_DEF_ME(mgdObj)

    me& me::_assign(const me& rhs) {
        _owns = rhs._owns->deepClone();
        _subs.bind(_makeNewSubs());
        _org = rhs._org;

        return *this;
    }

    me::mgdObj():
            super(), _shares(new scopes()), _owns(new scope()), _org(this) {
        _subs.bind(_makeNewSubs());
    }

    me::mgdObj(const scopes& shares, const scope& owns):
            super(), _shares(shares), _owns(owns), _org(this) {
        _subs.bind(_makeNewSubs());
    }

    me::mgdObj(const me& rhs): super(rhs) {
        _assign(rhs);
    }

    me& me::operator=(const me& rhs) {
        if (&rhs == this) return *this;

        super::operator=(rhs);

        return _assign(rhs);
    }

    nbicontainer& me::subs() { return *_subs; }

    scopes& me::getShares() { return *_shares; }

    scope& me::getOwns() { return *_owns; }

    const obj& me::getOrigin() const {
        return *_org;
    }

    scopes* me::_makeNewSubs() {
        scopes* ret = new scopes(*_owns);
        ret->link(*_shares);

        return ret;
    }
}
