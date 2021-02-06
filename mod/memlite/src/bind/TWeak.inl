#include "TWeak.hpp"
#include "TWeakTactic.hpp"
#include "TBindable.inl"

namespace wrd {

#define TEMPL template <typename T>
#define THIS TWeak<T>
#define SUPER Bind

    TEMPL THIS::TWeak() : SUPER(&TWeakTactic<T>::singletone) {}
    TEMPL THIS::TWeak(T& it) : SUPER(&TWeakTactic<T>::singletone) { this->bind(it); }
    TEMPL THIS::TWeak(T* it) : SUPER(&TWeakTactic<T>::singletone) { this->bind(*it); }
	TEMPL THIS::TWeak(const T& it) : SUPER(&TWeakTactic<const T>::singletone) { this->bind(it); }
	TEMPL THIS::TWeak(const T* it) : SUPER(&TWeakTactic<const T>::singletone) { this->bind(*it); }
    TEMPL THIS::TWeak(const Bind& rhs) { this->_assign(rhs); }
    TEMPL THIS::TWeak(BindTacticable* tactic): SUPER(tactic) {}

	TEMPL const T* THIS::operator->() const { return &this->get(); }
	TEMPL const T& THIS::operator*() const { return this->get(); }
	TEMPL T* THIS::operator->() { return &this->get(); }
	TEMPL T& THIS::operator*() { return this->get(); }

	TEMPL THIS& THIS::operator=(const Bind& rhs) {
        if(this == &rhs) return *this;

        SUPER::operator=(rhs);
		return *this;
	}

	TEMPL T& THIS::get() { return TBindable<Instance>::get<T>(); }
	TEMPL const T& THIS::get() const { return TBindable<Instance>::get<T>(); }
	TEMPL wbool THIS::bind(const T& new1) { return this->_bind(new1); }
    TEMPL wbool THIS::bind(T& new1) { return this->_bind(new1); }

#undef SUPER
#undef THIS
#undef TEMPL

}
