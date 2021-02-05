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
    TEMPL THIS::TStr(const Bind& rhs) : SUPER(&TStrTactic<T>::singletone) { this->_assign(rhs); }

#undef THIS
#define THIS    TStr<const T>

	TEMPL THIS::TStr(): SUPER(&TStrTactic<const T>::singletone) {}
	TEMPL THIS::TStr(T& it): SUPER(&TStrTactic<const T>::singletone) { this->bind(it); }
	TEMPL THIS::TStr(T* it): SUPER(&TStrTactic<const T>::singletone) { this->bind(*it); }
	TEMPL THIS::TStr(const T& it): SUPER(&TStrTactic<const T>::singletone) { this->bind(it); }
	TEMPL THIS::TStr(const T* it): SUPER(&TStrTactic<const T>::singletone) { this->bind(*it); }
	TEMPL THIS::TStr(const Bind& rhs): SUPER(&TStrTactic<const T>::singletone) { this->_assign(rhs); }

#undef TEMPL
#undef THIS
#undef SUPER

}
