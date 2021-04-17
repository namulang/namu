#include "tweak.hpp"
#include "weakTactic.hpp"
#include "tbindable.inl"

namespace wrd {

#define TEMPL template <typename T>
#define ME tweak<T>
#define SUPER binder

    TEMPL ME::tweak() : SUPER(ttype<T>::get(), weakTactic::singletone) {}
    TEMPL ME::tweak(const T& it): SUPER(ttype<T>::get(), weakTactic::singletone) { this->bind(it); }
    TEMPL ME::tweak(const T* it): SUPER(ttype<T>::get(), weakTactic::singletone) { this->bind(*it); }
    TEMPL ME::tweak(const ME& rhs): SUPER(ttype<T>::get(), weakTactic::singletone) { this->_assign(rhs); }
    TEMPL ME::tweak(const binder& rhs): SUPER(ttype<T>::get(), weakTactic::singletone) { this->_assign(rhs); }
    TEMPL ME::tweak(bindTacticable& tactic): SUPER(ttype<T>::get(), tactic) {}

	TEMPL T* ME::operator->() { return &this->get(); }
	TEMPL T& ME::operator*() { return this->get(); }

	TEMPL ME& ME::operator=(const binder& rhs) {
        if(this == &rhs) return *this;

        SUPER::operator=(rhs);
		return *this;
	}

	TEMPL T& ME::get() {
        instance& got = SUPER::get();
        if(nul(got)) return nulOf<T>();

        return got.cast<T>();
    }

    TEMPL wbool ME::bind(const T& new1) { return SUPER::bind(new1); }

#undef SUPER
#undef ME
#undef TEMPL

}
