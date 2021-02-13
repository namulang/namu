#include "TStr.hpp"
#include "TWeak.inl"
#include "StrTactic.hpp"

namespace wrd {

#define TEMPL	template <typename T>
#define THIS	TStr<T>
#define SUPER   TWeak<T>

    TEMPL THIS::TStr(): SUPER(StrTactic::singletone) {}
    TEMPL THIS::TStr(const T& it): SUPER(StrTactic::singletone) { this->bind(it); }
    TEMPL THIS::TStr(const T* it): SUPER(StrTactic::singletone) { this->bind(*it); }
    TEMPL THIS::TStr(const Bind& rhs): SUPER(StrTactic::singletone) { this->_assign(rhs); }

#undef SUPER
#undef THIS
#undef TEMPL

}
