#pragma once

namespace wrd {
    class typeProvidable {
        WRD_DECL_ME(typeProvidable)

    public:
        wbool operator==(const me& rhs) const {
            if(getType() != rhs.getType()) return false;

            return _onSame(rhs);
        }
        wbool operator!=(const me& rhs) const {
            return !operator==(rhs);
        }

        virtual const type& getType() const = 0;

        template <typename T>
        T& cast() {
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
