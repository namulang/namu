#pragma once

namespace wrd {
    class TypeProvidable {
        WRD_DECL_THIS(TypeProvidable)

    public:
        virtual const Type& getType() const = 0;

        template <typename T>
        T& cast() {
            if(!getType().isSub(TType<T>::get()))
                return nulOf<T>();

            return (T&) *this;
        }

        template <typename T>
        const T& cast() const WRD_UNCONST_FUNC(cast<T>())
    };
}
