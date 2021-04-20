#pragma once

#include "../common.hpp"

namespace wrd {
    /// means null-reference.
    template <typename T>
    T& nulOf() {
        T* ret = 0;
        return *ret;
    }

    template <typename T>
    wbool nul(T* any) {
        return !any;
    }

    template <typename T>
    wbool nul(T& any) {
        return !&any;
    }
}

