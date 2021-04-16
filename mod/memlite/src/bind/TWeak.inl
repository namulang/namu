#include "TWeak.hpp"
#include "WeakTactic.hpp"
#include "TBindable.inl"

namespace wrd {

#define TEMPL template <typename T>
#define ME TWeak<T>
#define SUPER Bind

    TEMPL ME::TWeak() : SUPER(TType<T>::get(), WeakTactic::singletone) {}
    TEMPL ME::TWeak(const T& it): SUPER(TType<T>::get(), WeakTactic::singletone) { this->bind(it); }
    TEMPL ME::TWeak(const T* it): SUPER(TType<T>::get(), WeakTactic::singletone) { this->bind(*it); }
    TEMPL ME::TWeak(const ME& rhs): SUPER(TType<T>::get(), WeakTactic::singletone) { this->_assign(rhs); }
    TEMPL ME::TWeak(const Bind& rhs): SUPER(TType<T>::get(), WeakTactic::singletone) { this->_assign(rhs); }
    TEMPL ME::TWeak(BindTacticable& tactic): SUPER(TType<T>::get(), tactic) {}

	TEMPL T* ME::operator->() { return &this->get(); }
	TEMPL T& ME::operator*() { return this->get(); }

	TEMPL ME& ME::operator=(const Bind& rhs) {
        if(this == &rhs) return *this;

        SUPER::operator=(rhs);
		return *this;
	}

	TEMPL T& ME::get() {
        Instance& got = SUPER::get();
        if(nul(got)) return nulOf<T>();

        return got.cast<T>();
    }

    TEMPL wbool ME::bind(const T& new1) { return SUPER::bind(new1); }

#undef SUPER
#undef ME
#undef TEMPL

}
