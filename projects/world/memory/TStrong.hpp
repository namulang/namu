#pragma once

#include "./TStrong.inl"
#include "./TWeak.hpp"

namespace wrd
{
#define TEMPL	template <typename T>
#define THIS	TStrong<T>
	
	WRD_CLASS_DEF(TEMPL, THIS)

    TEMPL THIS::TStrong() {}
    TEMPL THIS::TStrong(T& it) : Super() { this->bind(it); }
    TEMPL THIS::TStrong(T* it) : Super() { this->bind(*it); }
    TEMPL THIS::TStrong(const This& rhs) : Super() { this->assign(rhs); }
	TEMPL THIS::~TStrong() { unbind(); }

	TEMPL THIS& THIS::operator=(const This& rhs)
	{
		Super::operator=(rhs);
	    return *this;
	}
	
	TEMPL Res& THIS::unbind()
	{
	    Block& blk = this->_getBlock(this->getItsId());
		WRD_IS_NULL(blk, waswrongmember, Super::unbind())
	    blk._onStrong(-1);
	
	    return Super::unbind();
	}
	
	TEMPL Res& THIS::_bind(const Instance& it)
	{
		WRD_IS_SUPER(_bind(it));
		if( ! it.isHeap())
			return waswrongargs.warn("it is local variable. couldn't bind it strongly.");

		//  처음에 Instance가 Instancer에 생성되었을때는 strong==0 이며,
		//  StrongBinder가 붙지 않는다면 그대로 계속 메모리상주하게 된다.
		//  Strong이 Count.strong=0인 instance를 bind하는 순간, 이 instance는
		//  bind에 의해서 해제될 수 있게 된다.
		return this->_getBlock(this->getItsId())._onStrong(1);
	}

#undef THIS
#define THIS    TStrong<const T>

	WRD_CLASS_DEF(TEMPL, THIS)
	
	TEMPL THIS::TStrong() {}
	TEMPL THIS::TStrong(T& it) : Super() { this->bind(it); }
	TEMPL THIS::TStrong(T* it) : Super() { this->bind(*it); }
	TEMPL THIS::TStrong(const T& it) : Super() { this->bind(it); }
	TEMPL THIS::TStrong(const T* it) : Super() { this->bind(*it); }
	TEMPL THIS::TStrong(const This& rhs) : Super() { this->_assign(rhs); }
	TEMPL THIS::TStrong(const TStrong<T>& rhs) : Super() { this->_assign(rhs); }
	TEMPL THIS::~TStrong() { unbind(); }
	
	TEMPL THIS& THIS::operator=(const This& rhs)
	{
		Super::operator=(rhs);
	    return *this;
	}
	
	TEMPL THIS& THIS::operator=(const TStrong<T>& rhs)
	{
		Super::operator=(rhs);
	    return *this;
	}
	
	TEMPL Res& THIS::unbind()
	{
	     Block& blk = this->_getBlock(this->getItsId());
		 WRD_IS_NULL(blk, waswrongmember, Super::unbind())
	     blk._onStrong(-1);
	
	    return Super::unbind();
	}
	
	TEMPL Res& THIS::_bind(const Instance& it)
	{
	    WRD_IS_SUPER(_bind(it));
	    if( ! it.isHeap())
	        return waswrongargs.warn("it is local variable. couldn't bind it strongly.");
	
	    return this->_getBlock(this->getItsId())._onStrong(1);
	}

#undef TEMPL
#undef THIS
}
