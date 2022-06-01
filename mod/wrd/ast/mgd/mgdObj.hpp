#pragma once

#include "../obj.hpp"

namespace wrd {

    /// mgdObj is a object structured in managed programming environment like 'wrd'.
    /// owned sub nodes of a object can only be manipulated through API provided mgdObj.
    /// because native object won't have owned nodes but only shared ones.
    class _wout mgdObj : public obj {
        WRD(CLASS(mgdObj, obj))

    public:
        explicit mgdObj();
        explicit mgdObj(const scopes& shares, const scope& owns);
        explicit mgdObj(const me& rhs);

        me& operator=(const me& rhs);

        using super::subs;
        nbicontainer& subs() override;

        scopes& getShares();
        const scopes& getShares() const WRD_UNCONST_FUNC(getShares())

        scope& getOwns();
        const scope& getOwns() const WRD_UNCONST_FUNC(getOwns())

        const obj& getOrigin() const override;

        const point& getPos() const override { return _pos; }
        void setPos(const point& new1) override { _pos = new1; }

    private:
        scopes* _makeNewSubs();

        me& _assign(const me& rhs);

    private:
        tstr<scopes> _subs;
        tstr<scopes> _shares;
        tstr<scope> _owns;
        obj* _org;
        point _pos;
    };
}
