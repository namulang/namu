#pragma once

#include "TWeak.inl"
#include "../memory/Block.hpp"
#include "../meta/helpers.hpp"
#include "../pretypes/Reses.hpp"
#include "../meta/TClass.hpp"

namespace wrd
{
#define TEMPL template <typename T>
#define THIS TWeak<T>

	WRD_CLASS_DEF(TEMPL, THIS)

    TEMPL THIS::TWeak() { }
    TEMPL THIS::TWeak(T& it) { this->bind(it); }
    TEMPL THIS::TWeak(T* it) { this->bind(*it); }
    TEMPL THIS::TWeak(const This& rhs) { this->_assign(rhs); }
	TEMPL const T* THIS::operator->() const { return &this->get(); }
	TEMPL const T& THIS::operator*() const { return this->get(); }
	TEMPL T* THIS::operator->() { return &this->get(); }
	TEMPL T& THIS::operator*() { return this->get(); }

	TEMPL THIS& THIS::operator=(const This& rhs)
	{
		Super::operator=(rhs);
		return *this;
	}

	TEMPL Res& THIS::bind(T& new1) { return this->bind(new1); }
	
	TEMPL Res& THIS::unbind()
	{
	    Block& blk = WRD_GET(this->_getBlock(this->getItsId()));
	    blk._onWeak(-1);
	    return Super::unbind();
	}
	
	TEMPL const Class& THIS::getBindable() const { return T::getClassStatic(); }
	
	TEMPL T& THIS::get()
	{
	    Instance& got = WRD_GET(_get(), nulr<T>());
	    return got.down<T>();
	}
	
	TEMPL const T& THIS::get() const
	{
	    WRD_UNCONST()
	    return unconst.get();
	}
	
	TEMPL wbool THIS::isConst() const { return false; }
	
	TEMPL Res& THIS::_bind(const Instance& it)
    {
        //  pre:
        //      param-validation:
        Block& blk = WRD_GET(const_cast<Block&>(it.getBlock()));

        //  main:
        unbind();
        this->_setId(it.getId());
        return blk._onWeak(1);
    }

#undef THIS
#define THIS TWeak<const T>

	WRD_CLASS_DEF(TEMPL, THIS)

	TEMPL THIS::TWeak() { }
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
	    WRD_ASSIGN_GUARD()
	
		Super::operator=(rhs);
	    return *this;
	}

	TEMPL THIS& THIS::operator=(const TWeak<T>& rhs)
	{
		WRD_ASSIGN_GUARD()

		Super::operator=(rhs);
		return *this;
	}

	TEMPL Res& THIS::bind(T& new1) { return this->bind(new1); }
	TEMPL Res& THIS::bind(const T& new1) { return this->bind(new1); }
	
	TEMPL Res& THIS::unbind()
	{
	    Block& blk = WRD_GET(this->_getBlock(this->getItsId()));
	    blk._onWeak(-1);
	    return this->Super::unbind();
	}
	
	TEMPL const Class& THIS::getBindable() const { return T::getClassStatic(); }
	
	TEMPL const T& THIS::get() const
	{
	    WRD_UNCONST()
	    const Instance& got = WRD_GET(unconst._get(), nulr<T>());
	    return got.down<T>();
	}
	
	TEMPL wbool THIS::isConst() const { return false; }
	
	TEMPL Res& THIS::_bind(const Instance& it)
	{
		WRD_IS_SUPER(_bind(it))

		Block& blk = WRD_GET(const_cast<Block&>(it.getBlock()));
	    return blk._onWeak(1);
	}

#undef THIS
#undef TEMPL

}
