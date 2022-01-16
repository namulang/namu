#pragma once

#include "tstr.hpp"
#include "tweak.inl"
#include "strTactic.hpp"

namespace wrd {

#define TEMPL	template <typename T>
#define ME	tstr<T>
#define SUPER   tweak<T>

    TEMPL ME::tstr(): SUPER(strTactic::singletone) {}
    TEMPL ME::tstr(const T& it): SUPER(strTactic::singletone) { this->bind(it); }
    TEMPL ME::tstr(const T* it): SUPER(strTactic::singletone) { this->bind(*it); }
    TEMPL ME::tstr(const ME& rhs): SUPER(strTactic::singletone) { this->_assign(rhs); }
    TEMPL ME::tstr(const binder& rhs): SUPER(strTactic::singletone) { this->_assign(rhs); }

#undef SUPER
#undef ME
#undef TEMPL

}
