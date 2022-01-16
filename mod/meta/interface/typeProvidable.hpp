#pragma once

namespace wrd {
    class typeProvidable {
        WRD_DECL_ME(typeProvidable)

    public:
        wbool operator==(const me& rhs) const {
            if(nul(rhs)) return false;
            if(getType() != rhs.getType()) return false;

            return _onSame(rhs);
        }
        wbool operator!=(const me& rhs) const {
            return !operator==(rhs);
        }

        virtual const type& getType() const = 0;

        template <typename T>
        T& cast() {
            // this protection:
            //  this c wrd interpreter uses references in default, and not any pointers.
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

            if(!getType().isSub(ttype<T>::get()))
                return nulOf<T>();

            return (T&) *this;
        }

        template <typename T>
        const T& cast() const WRD_UNCONST_FUNC(cast<T>())

    protected:
        virtual wbool _onSame(const me& rhs) const {
            return this == &rhs;
        }
    };
}
