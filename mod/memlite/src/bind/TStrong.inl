#include "TStrong.hpp"
#include "TWeak.inl"
#include "TStrongTactic.hpp"

namespace wrd {

#define TEMPL	template <typename T>
#define THIS	TStrong<T>
#define SUPER   TWeak<T>

    TEMPL THIS::TStrong(): SUPER(&TStrongTactic<T>::singletone) {}
    TEMPL THIS::TStrong(T& it): SUPER(&TStrongTactic<T>::singletone) { this->bind(it); }
    TEMPL THIS::TStrong(T* it): SUPER(&TStrongTactic<T>::singletone) { this->bind(*it); }
    TEMPL THIS::TStrong(const Bind& rhs) : SUPER(&TStrongTactic<T>::singletone) { this->_assign(rhs); }

#undef THIS
#define THIS    TStrong<const T>

	TEMPL THIS::TStrong(): SUPER(&TStrongTactic<const T>::singletone) {}
	TEMPL THIS::TStrong(T& it): SUPER(&TStrongTactic<const T>::singletone) { this->bind(it); }
	TEMPL THIS::TStrong(T* it): SUPER(&TStrongTactic<const T>::singletone) { this->bind(*it); }
	TEMPL THIS::TStrong(const T& it): SUPER(&TStrongTactic<const T>::singletone) { this->bind(it); }
	TEMPL THIS::TStrong(const T* it): SUPER(&TStrongTactic<const T>::singletone) { this->bind(*it); }
	TEMPL THIS::TStrong(const Bind& rhs): SUPER(&TStrongTactic<const T>::singletone) { this->_assign(rhs); }

#undef TEMPL
#undef THIS
#undef SUPER

}
