#pragma once

#include "baseObj.hpp"
#include "scope.hpp"

namespace namu {

    /// obj is a object structured in managed programming environment like 'namu'.
    /// owned sub nodes of a object can only be manipulated through API provided obj.
    /// because native object won't have owned nodes but only shared ones.
    class _nout obj : public baseObj {
        NAMU(CLASS(obj, baseObj), VISIT())
        friend class slot; // for _onRunSub

    public:
        explicit obj();
        explicit obj(const scopes& shares, const scope& owns);
        explicit obj(const me& rhs);

        me& operator=(const me& rhs);

        using super::subs;
        nbicontainer& subs() override;

        scopes& getShares();
        const scopes& getShares() const NAMU_UNCONST_FUNC(getShares())
        scope& getOwns();
        const scope& getOwns() const NAMU_UNCONST_FUNC(getOwns())
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

#ifdef NAMU_BUILD_PLATFORM_IS_WINDOWS
    // f***ing annoying another MSVC bug here:
    //  first of all, I'm so sorry to start my slang. but I couldn't help spitting it out after
    //  I used plenty hours of heading to the ground.
    //
    //  I don't know why, but unless define below variable here, I'll observe that the member-variable
    //  '_subs' above was tried to be instantiated but failed.
    //  error message said that 'You've used undefined type "identifiertstr<scopes>"'.
    //  however, MSVC definately knows about tstr<T> and scopes types.
    //
    //  clang, gcc didn't complain about this.
    namespace {
        static const inline scopes a3;
    }
#endif
}
