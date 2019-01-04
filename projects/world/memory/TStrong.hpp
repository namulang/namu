#pragma once

#include "./TStrong.inl"
#include "./TWeak.hpp"

namespace wrd
{
#define TEMPL	template <typename T>
#define THIS	TStrong<T>
	
	WRD_CLASS_DEF(TEMPL, THIS)

    TEMPL THIS::TStrong() {}
    TEMPL THIS::TStrong(T& it) : Super() { bind(it); }
    TEMPL THIS::TStrong(T* it) : Super() { bind(it); }
    TEMPL THIS::TStrong(This& it) : Super() { bind(*it); }
    TEMPL THIS::TStrong(This* it) : Super() { bind(*it); }

	TEMPL THIS& THIS::operator=(This& rhs)
	{
	    WRD_ASSIGN_GUARD()
	
	    bind(*rhs);
	    return *this;
	}
	
	TEMPL Res& THIS::unbind()
	{
	    Block& blk = WRD_GET(this->_getBlock(getItsId()), waswrongmember, Super::unbind());
	    blk._onStrong(-1);
	
	    return Super::unbind();
	}
	
	TEMPL Res& THIS::_bind(const Instance& it)
	{
		WRD_IS_SUPER(bind(it));
		if( ! it.isHeap())
			return waswrongargs.warn("it is local variable. couldn't bind it strongly.");

		//  처음에 Instance가 Instancer에 생성되었을때는 strong==0 이며,
		//  StrongBinder가 붙지 않는다면 그대로 계속 메모리상주하게 된다.
		//  Strong이 Count.strong=0인 instance를 bind하는 순간, 이 instance는
		//  bind에 의해서 해제될 수 있게 된다.
		return this->_getBlock(getItsId())._onStrong(1);
	}

#undef THIS
#define THIS    TStrong<const T>

	WRD_CLASS_DEF(TEMPL, THIS)
	
	TEMPL THIS::TStrong() {}
	TEMPL THIS::TStrong(T& it) : Super() { bind(it); }
	TEMPL THIS::TStrong(T* it) : Super() { bind(it); }
	TEMPL THIS::TStrong(const T& it) : Super() { bind(it); }
	TEMPL THIS::TStrong(const T* it) : Super() { bind(it); }
	TEMPL THIS::TStrong(This& it) : Super() { bind(*it); }
	TEMPL THIS::TStrong(This* it) : Super() { bind(*it); }
	TEMPL THIS::TStrong(const This& it) : Super() { bind(*it); }
	TEMPL THIS::TStrong(const This* it) : Super() { bind(*it); }
	
	TEMPL THIS& THIS::operator=(This& rhs)
	{
	    WRD_ASSIGN_GUARD()
	
	    bind(*rhs);
	    return *this;
	}
	
	TEMPL THIS& THIS::operator=(const This& rhs)
	{
	    WRD_ASSIGN_GUARD()
	
	    bind(*rhs);
	    return *this;
	}
	
	TEMPL Res& THIS::unbind()
	{
	     Block& blk = WRD_GET(this->_getBlock(), waswrongmember, Super::unbind());
	     blk.unlink();
	     Block& blk = WRD_GET(this->_getBlock(getItsId()), waswrongmember, Super::unbind());
	     blk._onStrong(-1);
	
	    return Super::unbind();
	}
	
	TEMPL Res& THIS::_bind(const Instance& it)
	{
	    WRD_IS_SUPER(bind(it));
	    if( ! it.isHeap())
	        return waswrongargs.warn("it is local variable. couldn't bind it strongly.");
	
	    return this->_getBlock(getItsId())._onStrong(1);
	}

#undef TEMPL
#undef THIS
}

#undef TEMPL
#undef THIS
}
