#pragma once

#include "../common.hpp"

namespace namu {
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
    inline wbool nul(T& any) {
        // reference-null-check hack:
        //  in c++ standard reference, it's not allow to check pointer of reference whether
        //  it's null or not, it's always regarded to not null.
        //
        //  however, in namu project, I decided to use only reference for some reason and
        //  treat it like a pointer. instead, I won't declare a pointer at all.
        //
        //  so we need to check nulity of a reference but compiler always optimize it to true
        //  when it meets checking of a pointer to a reference.
        //  but if we do some pointer arithmetic to an address of nulled reference, it won't be
        //  optimized.
        //  and we need to add '1' as a pointer to char type. because it's the only type that
        //  we can guarantee it'll be always size 1 when this software is built on any platform or
        //  architecture.
        return ((char*) &any) + 1 == (char*) 1;
    }
}

