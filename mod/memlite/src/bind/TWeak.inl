#include "TWeak.hpp"
#include "WeakTactic.hpp"
#include "TBindable.inl"

namespace wrd {

#define TEMPL template <typename T>
#define THIS TWeak<T>
#define SUPER Bind

    TEMPL THIS::TWeak() : SUPER(TType<T>::get(), WeakTactic::singletone) {}
    TEMPL THIS::TWeak(T& it) : SUPER(TType<T>::get(), WeakTactic::singletone) { this->bind(it); }
    TEMPL THIS::TWeak(T* it) : SUPER(TType<T>::get(), WeakTactic::singletone) { this->bind(*it); }
    TEMPL THIS::TWeak(Bind& rhs) { this->_assign(rhs); }
    TEMPL THIS::TWeak(BindTacticable& tactic): SUPER(TType<T>::get(), tactic) {}

	TEMPL T* THIS::operator->() { return &this->get(); }
	TEMPL T& THIS::operator*() { return this->get(); }

	TEMPL THIS& THIS::operator=(Bind& rhs) {
        if(this == &rhs) return *this;

        SUPER::operator=(rhs);
		return *this;
	}

	TEMPL T& THIS::get() {
        Instance& got = SUPER::get();
        WRD_NUL(got, nulOf<T>())
        if(!got.getType().isSub(TType<T>::get()))
            return nulOf<T>();

        return (T&) got;
    }
    TEMPL wbool THIS::bind(T& new1) { return SUPER::bind(new1); }

#undef SUPER
#undef THIS
#undef TEMPL

}
