#include "TStr.hpp"
#include "TWeak.inl"
#include "StrTactic.hpp"

namespace wrd {

#define TEMPL	template <typename T>
#define ME	TStr<T>
#define SUPER   TWeak<T>

    TEMPL ME::TStr(): SUPER(StrTactic::singletone) {}
    TEMPL ME::TStr(const T& it): SUPER(StrTactic::singletone) { this->bind(it); }
    TEMPL ME::TStr(const T* it): SUPER(StrTactic::singletone) { this->bind(*it); }
    TEMPL ME::TStr(const ME& rhs): SUPER(StrTactic::singletone) { this->_assign(rhs); }
    TEMPL ME::TStr(const Bind& rhs): SUPER(StrTactic::singletone) { this->_assign(rhs); }

#undef SUPER
#undef ME
#undef TEMPL

}
