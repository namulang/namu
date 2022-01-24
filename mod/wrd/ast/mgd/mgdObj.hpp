#pragma once

#include "../obj.hpp"

namespace wrd {

    /// mgdObj is a object structured in managed programming environment like 'wrd'.
    /// owned sub nodes of a object can only be manipulated through API provided mgdObj.
    /// because native object won't have owned nodes but only shared ones.
    class mgdObj : public obj {
        WRD(INTERFACE(mgdObj, obj))

    public:
        explicit mgdObj()
            : super(), _shares(new nchain()), _owns(new narr()), _org(this) {
            _subs.bind(_makeNewSubs());
        }
        explicit mgdObj(const std::string& name)
            : super(name), _shares(new nchain()), _owns(new narr()), _org(this) {
            _subs.bind(_makeNewSubs());
        }
        explicit mgdObj(const std::string& name, const nchain& shares, const narr& owns)
            : super(name), _shares(shares), _owns(owns), _org(this) {
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

        nchain& getShares() { return *_shares; }
        const nchain& getShares() const WRD_UNCONST_FUNC(getShares())

        narr& getOwns() { return *_owns; }
        const narr& getOwns() const WRD_UNCONST_FUNC(getOwns())

        const obj& getOrigin() const override {
            return *_org;
        }

        using super::run;
        str run(const std::string& name, const containable& args) override;

    private:
        nchain* _makeNewSubs() {
            nchain* ret = new nchain(*_owns);
            ret->link(*_shares);

            return ret;
        }

        me& _assign(const me& rhs);

    private:
        tstr<nchain> _shares;
        tstr<narr> _owns;
        obj* _org;
    };
}
