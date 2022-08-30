#include "obj.hpp"
#include "visitor.hpp"

namespace namu {

    NAMU(DEF_ME(obj), DEF_VISIT())

    me& me::_assign(const me& rhs) {
        _owns = rhs._owns->deepClone();
        _shares.bind(*rhs._shares);
        _subs.bind(_makeNewSubs());
        _org = rhs._org;
        _pos = rhs._pos;

        return *this;
    }

    me::obj():
            super(), _shares(new scopes()), _owns(new scope()), _org(this) {
        _subs.bind(_makeNewSubs());
    }

    me::obj(const scopes& shares, const scope& owns):
            super(), _shares(shares), _owns(owns), _org(this) {
        _subs.bind(_makeNewSubs());
    }

    me::obj(const me& rhs): super(rhs) {
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
