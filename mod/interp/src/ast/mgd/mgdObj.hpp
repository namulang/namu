#pragma once

#include "../obj.hpp"

namespace wrd {

    class mgdObj : public obj {
        WRD_INTERFACE(mgdObj, obj)

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

    protected:
        wbool _onInFrame(frame& fr, const ncontainer& args) override;
        wbool _onOutFrame(frame& fr, const ncontainer& args) override;

    private:
        me& _assign(const me& rhs);

    private:
        tstr<nchain> _shares;
        obj* _org;
    };
}
