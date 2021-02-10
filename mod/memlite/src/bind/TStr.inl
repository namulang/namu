#include "TStr.hpp"
#include "TWeak.inl"
#include "TStrTactic.hpp"

namespace wrd {

#define TEMPL	template <typename T>
#define THIS	TStr<T>
#define SUPER   TWeak<T>

    TEMPL THIS::TStr(): SUPER(&TStrTactic<T>::singletone) {}
    TEMPL THIS::TStr(T& it): SUPER(&TStrTactic<T>::singletone) { this->bind(it); }
    TEMPL THIS::TStr(T* it): SUPER(&TStrTactic<T>::singletone) { this->bind(*it); }
    TEMPL THIS::TStr(Bind& rhs): SUPER(&TStrTactic<T>::singletone) { this->_assign(rhs); }

#undef SUPER
#undef THIS
#undef TEMPL

}
