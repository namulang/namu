#pragma once

#include "TWeak.inl"
#include "../memory/Block.hpp"
#include "../meta/helpers.hpp"

namespace wrd
{
#define TEMPL template <typename T>
#define THIS TWeak<T>

	WRD_CLASS_DEF(TEMPL, THIS)

    TEMPL THIS::TWeak() { }
    TEMPL THIS::TWeak(T& it) { this->bind(it); }
    TEMPL THIS::TWeak(T* it) { this->bind(it); }
    TEMPL THIS::TWeak(This& it) { this->bind(it); }
    TEMPL THIS::TWeak(This* it) { this->bind(it); }
	TEMPL const T* THIS::operator->() const { return &get(); }
	TEMPL const T* THIS::operator*() const { return &get(); }
	TEMPL T* THIS::operator->() { return &get(); }
	TEMPL T* THIS::operator*() { return &get(); }

	TEMPL This& THIS::operator=(const This& rhs)
	{
		WRD_ASSIGN_GUARD()

		this->bind(rhs);
		return *this;
	}

	TEMPL Res& THIS::bind(T& new1) { return bind(new1); }
	
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
	    return got.cast<T>();
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
        Block& blk = WRD_GET(const_cast<Block&>(new1.getBlock()));

        //  main:
        unbind();
        this->_setId(new1.getId());
        this->_setSerial(blk.getSerial());
        return blk._onWeak(1);
    }

#undef THIS
#define THIS TWeak<const T>

	WRD_CLASS_DEF(TEMPL, THIS)

	TEMPL THIS::TWeak() { }
	TEMPL THIS::TWeak(T& it) { this->bind(it); }
	TEMPL THIS::TWeak(T* it) { this->bind(it); }
	TEMPL THIS::TWeak(This& it) { this->bind(it); }
	TEMPL THIS::TWeak(This* it) { this->bind(it); }
	TEMPL THIS::TWeak(const T& it) { this->bind(it); }
	TEMPL THIS::TWeak(const T* it) { this->bind(it); }
	TEMPL THIS::TWeak(const This& it) { this->bind(it); }
	TEMPL THIS::TWeak(const This* it) { this->bind(it); }
	TEMPL const T* THIS::operator->() const { return &get(); }
	TEMPL const T* THIS::operator*() const { return &get(); }

	TEMPL This& THIS::operator=(This& rhs)
	{
	    WRD_ASSIGN_GUARD()
	
	    bind(rhs);
	    return *this;
	}

	TEMPL This& THIS::operator=(const This& rhs)
	{
		WRD_ASSIGN_GUARD()

		bind(rhs);
		return *this;
	}

	TEMPL Res& THIS::bind(T& new1) { return bind(new1); }
	TEMPL Res& THIS::bind(const T& new1) { return bind(new1); }
	
	TEMPL Res& THIS::unbind()
	{
	    Block& blk = WRD_GET(this->_getBlock(this->getItsId()));
	    blk._onWeak(-1);
	    return Super::unbind();
	}
	
	TEMPL const Class& THIS::getBindable() const { return T::getClassStatic(); }
	
	TEMPL const T& THIS::get() const
	{
	    WRD_UNCONST()
	    const Instance& got = WRD_GET(unconst._get(), nulr<T>());
	    return got.cast<T>();
	}
	
	TEMPL wbool THIS::isConst() const { return false; }
	
	TEMPL Res& THIS::_bind(const Instance& it)
	{
	    //  pre:
	    //      param-validation:
	    Block& blk = WRD_GET(const_cast<Block&>(new1.getBlock()));
	
	    //  main:
	    unbind();
	    this->_setId(new1.getId());
	    this->_setSerial(blk.getSerial());
	    return blk._onWeak(1);
	}

#undef THIS
#undef TEMPL

}
