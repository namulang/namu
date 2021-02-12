#pragma once

namespace wrd {
    struct TypeProvidable {
        virtual Type& getType() = 0;

        template <typename T>
        T& cast() {
            if(!getType().isSub(TType<T>::get()))
                return nulOf<T>();

            return (T&) *this;
        }
    };
}
