#pragma once

#include "./TStrong.inl"
#include "./TWeak.hpp"

namespace wrd
{
#define TEMPL	template <typename T>
#define THIS	TStrong<T>
	
	WRD_CLASS_DEFINE(TEMPL, THIS)

    TEMPL THIS::TStrong() {}
    TEMPL THIS::TStrong(const T& it) : Super() { bind(it); }
    TEMPL THIS::TStrong(const T* it) : Super() { bind(it); }

    TEMPL Res& THIS::bind(const T& it)
	{
		Res& res = Super::bind(it);
		if(res)
			return res.warn("...");
		if( ! it.isHeap())
			return waswrongargs.warn("it is local variable. couldn't bind it strongly.");

		//  처음에 Instance가 Instancer에 생성되었을때는 strong==0 이며,
		//  StrongBinder가 붙지 않는다면 그대로 계속 메모리상주하게 된다.
		//  Strong이 Count.strong=0인 instance를 bind하는 순간, 이 instance는
		//  bind에 의해서 해제될 수 있게 된다.
		return this->_getBlock().link();
	}

	TEMPL Res& THIS::unbind()
	{
		Block& blk = this->_getBlock();
		WRD_IS_NULL(blk, waswrongmember, Super::unbind())
		blk.unlink();

		return Super::unbind();
	}

#undef TEMPL
#undef THIS
}
