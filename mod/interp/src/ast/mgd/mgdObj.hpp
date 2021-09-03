#pragma once

#include "../obj.hpp"

namespace wrd {

    /// mgdObj is a object structured in managed programming environment like 'wrd'.
    /// owned sub nodes of a object can only be manipulated through API provided mgdObj.
    /// because native object won't have owned nodes but only shared ones.
    class mgdObj : public obj {
        WRD(INTERFACE(mgdObj, obj))

    public:
        explicit mgdObj(const std::string& name = "")
            : super(name), _shares(new nchain()), _org(this) {
            _subs->link(*_shares);
        }
        explicit mgdObj(const me& rhs): super(rhs) {
            _assign(rhs);
        }

        me& operator=(const me& rhs) {
            if (&rhs == this) return *this;

            super::operator=(rhs);

            return _assign(rhs);
        }

        ncontainer& getShares() {
            return *_shares;
        }
        const ncontainer& getShares() const WRD_UNCONST_FUNC(getShares())

        const obj& getOrigin() const override {
            return *_org;
        }

    private:
        me& _assign(const me& rhs);

    private:
        tstr<nchain> _shares;
        obj* _org;
    };
}
