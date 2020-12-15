#include "TWeak.hpp"

namespace wrd { namespace memlite {

#define TEMPL template <typename T>
#define THIS TWeak<T>
#define SUPER Bind

    TEMPL THIS::TWeak() {}
    TEMPL THIS::TWeak(T& it) { this->bind(it); }
    TEMPL THIS::TWeak(T* it) { this->bind(*it); }
    TEMPL THIS::TWeak(const This& rhs) { this->_assign(rhs); }
	TEMPL const T* THIS::operator->() const { return &this->get(); }
	TEMPL const T& THIS::operator*() const { return this->get(); }
	TEMPL T* THIS::operator->() { return &this->get(); }
	TEMPL T& THIS::operator*() { return this->get(); }

	TEMPL THIS& THIS::operator=(const This& rhs)
	{
        if(this == &rhs) return *this;

		SUPER::operator=(rhs);
		return *this;
	}

	TEMPL wbool THIS::bind(T& new1) { return this->_bind(new1); }
	TEMPL const Type& THIS::getBindable() const { return TType<T>::get(); }
	
	TEMPL T& THIS::get() { return SUPER::get(); }
	TEMPL const T& THIS::get() const { return SUPER::get(); }
	TEMPL wbool THIS::isConst() const { return false; }
	
#undef THIS
#define THIS TWeak<const T>

	TEMPL THIS::TWeak() {}
	TEMPL THIS::TWeak(T& it) { this->bind(it); }
	TEMPL THIS::TWeak(T* it) { this->bind(*it); }
	TEMPL THIS::TWeak(const T& it) { this->bind(it); }
	TEMPL THIS::TWeak(const T* it) { this->bind(*it); }
	TEMPL THIS::TWeak(const This& rhs) { this->_assign(rhs); }
	TEMPL THIS::TWeak(const TWeak<T>& rhs) { this->_assign(rhs); }
	TEMPL const T* THIS::operator->() const { return &this->get(); }
	TEMPL const T& THIS::operator*() const { return this->get(); }

	TEMPL THIS& THIS::operator=(const This& rhs)
	{
        if(this == &rhs) return *this;
	
		SUPER::operator=(rhs);
	    return *this;
	}

	TEMPL THIS& THIS::operator=(const TWeak<T>& rhs)
	{
        if(this == &rhs) return *this;

		SUPER::operator=(rhs);
		return *this;
	}

	TEMPL wbool THIS::bind(T& new1) { return this->_bind(new1); }
	TEMPL wbool THIS::bind(const T& new1) { return this->_bind(new1); }
	TEMPL const Type& THIS::getBindable() const { return TType<T>::get(); }
	TEMPL const T& THIS::get() const { return SUPER::get(); }
	TEMPL wbool THIS::isConst() const { return true; }

#undef THIS
#undef TEMPL
#undef SUPER

}}
