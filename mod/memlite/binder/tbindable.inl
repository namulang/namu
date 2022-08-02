#pragma once

#include "tbindable.hpp"

namespace namu {

#define TEMPL template <typename T>
#define ME tbindable<T>

    TEMPL ME::operator wbool() const { return isBind(); }

    TEMPL wbool ME::canBind(const T& it) const {
        if(nul(it)) return false;
        return canBind(it.getType());
    }

    TEMPL
    wbool ME::bind(const T& it) {
        // type checking before binding only is required to Bind class.
        // Derived classes from this doesn't need it. because its type is specified.
        // prevent wrong type providing by compiler.
        if(!canBind(it)) return false;
        return true;
    }

    TEMPL
    wbool ME::bind(const T* it) { return bind(*it); }

#undef ME
#undef TEMPL
}
