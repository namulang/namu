#include "TWeak.hpp"
#include "WeakTactic.hpp"
#include "TBindable.inl"

namespace wrd {

#define TEMPL template <typename T>
#define THIS TWeak<T>
#define SUPER Bind

    TEMPL THIS::TWeak() : SUPER(TType<T>::get(), WeakTactic::singletone) {}
    TEMPL THIS::TWeak(const T& it): SUPER(TType<T>::get(), WeakTactic::singletone) { this->bind(it); }
    TEMPL THIS::TWeak(const T* it): SUPER(TType<T>::get(), WeakTactic::singletone) { this->bind(*it); }
    TEMPL THIS::TWeak(const THIS& rhs): SUPER(TType<T>::get(), WeakTactic::singletone) { this->_assign(rhs); }
    TEMPL THIS::TWeak(const Bind& rhs): SUPER(TType<T>::get(), WeakTactic::singletone) { this->_assign(rhs); }
    TEMPL THIS::TWeak(BindTacticable& tactic): SUPER(TType<T>::get(), tactic) {}

	TEMPL T* THIS::operator->() { return &this->get(); }
	TEMPL T& THIS::operator*() { return this->get(); }

	TEMPL THIS& THIS::operator=(const Bind& rhs) {
        if(this == &rhs) return *this;

        SUPER::operator=(rhs);
		return *this;
	}

	TEMPL T& THIS::get() {
        Instance& got = SUPER::get();
        if(nul(got)) return nulOf<T>();

        return got.cast<T>();
    }

    TEMPL wbool THIS::bind(const T& new1) { return SUPER::bind(new1); }

#undef SUPER
#undef THIS
#undef TEMPL

}
