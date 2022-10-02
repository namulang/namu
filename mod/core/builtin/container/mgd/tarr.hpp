#pragma once

#include "arr.hpp"

namespace namu {

    template <typename T>
    class tarr : public arr {
        NAMU(CLASS(tarr, arr))

    public:
        tarr(): super(ttype<T>::get()) {}
        tarr(arr& rhs): super(rhs) {}
    };
}
