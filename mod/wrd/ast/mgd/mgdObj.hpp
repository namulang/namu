#pragma once

#include "../obj.hpp"

namespace wrd {

    /// mgdObj is a object structured in managed programming environment like 'wrd'.
    /// owned sub nodes of a object can only be manipulated through API provided mgdObj.
    /// because native object won't have owned nodes but only shared ones.
    class _wout mgdObj : public obj {
        WRD(CLASS(mgdObj, obj))

    public:
        explicit mgdObj()
            : super(), _shares(new scopes()), _owns(new scope()), _org(this) {
            _subs.bind(_makeNewSubs());
        }
        explicit mgdObj(const scopes& shares, const scope& owns)
            : super(), _shares(shares), _owns(owns), _org(this) {
            _subs.bind(_makeNewSubs());
        }
        explicit mgdObj(const me& rhs): super(rhs) {
            _assign(rhs);
        }

        me& operator=(const me& rhs) {
            if (&rhs == this) return *this;

            super::operator=(rhs);

            return _assign(rhs);
        }

        using super::subs;
        nbicontainer& subs() override { return *_subs; }

        scopes& getShares() { return *_shares; }
        const scopes& getShares() const WRD_UNCONST_FUNC(getShares())

        scope& getOwns() { return *_owns; }
        const scope& getOwns() const WRD_UNCONST_FUNC(getOwns())

        const obj& getOrigin() const override {
            return *_org;
        }

    private:
        scopes* _makeNewSubs() {
            scopes* ret = new scopes(*_owns);
            ret->link(*_shares);

            return ret;
        }

        me& _assign(const me& rhs);

    private:
        tstr<scopes> _subs;
        tstr<scopes> _shares;
        tstr<scope> _owns;
        obj* _org;
    };
}
