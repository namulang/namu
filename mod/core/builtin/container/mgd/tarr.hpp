#pragma once

#include "arr.hpp"

namespace namu {

    template <typename T>
    class tarr : public arr {
        NAMU(ME(tarr, arr),
             INIT_META(tarr),
             CLONE(tarr))

    public:
        tarr(): super(*new T()) {}
        tarr(arr& rhs): super(rhs) {}
    };
}
