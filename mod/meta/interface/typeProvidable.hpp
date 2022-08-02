#pragma once

#include "../common.hpp"

namespace namu {
    class _wout typeProvidable {
        WRD_DECL_ME(typeProvidable)

    public:
        wbool operator==(const me& rhs) const;
        wbool operator!=(const me& rhs) const;

    public:
        virtual const type& getType() const = 0;
        wbool isSub(const type& it) const;
        wbool isSub(const typeProvidable& it) const {
            return isSub(it.getType());
        }
        wbool isSuper(const type& it) const;
        template <typename T> wbool isSub() const { return getType().isSub<T>(); }
        template <typename T> wbool isSuper() const { return getType().isSuper<T>(); }

        template <typename T>
        T& cast() {
            // this protection:
            //  this c namu interpreter uses references in default, and not any pointers.
            //  so you always care about a refer can be nulled.
            //  for a convenience of our API users I put this guard.
            //
            //  please note that checking whether thisptr is null isn't recommended in
            //  ordinary cpp.
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-undefined-compare"
            if (this == nullptr)
                return nulOf<T>();
#pragma clang diagnostic pop

            return *(T*) cast(ttype<T>::get());
        }

        template <typename T> const T& cast() const WRD_UNCONST_FUNC(cast<T>())

        virtual void* cast(const type& to);
        const void* cast(const type& to) const WRD_UNCONST_FUNC(cast(to))

    protected:
        virtual wbool _onSame(const me& rhs) const;
    };
}
