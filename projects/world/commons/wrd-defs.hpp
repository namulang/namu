#pragma once

#include "wrd-deps.hpp"

//	World는 객체 안에서 다른 객체에 접근하는 접근자함수들에 경우에는 DelayingNullCorruption으로 인해 객체가 Null이라고 해도 Null을 반환할뿐 프로그램이 죽지는 않는다.
//	접근자 아닌 경우에는 "속도문제" 로 인해 수행하지 않는다.
//	또한 반환형이 객체에 대한 레퍼런스나 포인터가 아닌경우에도 정상적인 반환값과 겹칠 수있기 때문에 체크하지 않는다.
#define WRD_IS_NULL_2(VALUE, RET)	\
	if((VALUE.isNull())) {			\
		RET.warn(#VALUE);			\
		return RET;					\
	}
#define WRD_IS_NULL_1(VALUE)		\
	WRD_IS_NULL_2(VALUE, NullPtr)
#define WRD_IS_NULL(...) WRD_MACRO_OVERLOADER(WRD_IS_NULL, __VA_ARGS__)

//	multiple NULL check macro:
//		if you need to check plenty arguments to be checked null
//		and return value will be same, you can accomplish it conveniently
//		with this macro.
//
//		usage:
//			WRD_IS_NULL(arg1, -1)
//			WRD_IS_NULL(arg2, -1)
//			WRD_IS_NULL(arg3, -1)
//				or
//			WRD_ARE_NULL(-1, arg1, arg2, arg3)
#define _ARE_NULL(VALUE, RET)		WRD_IS_NULL(VALUE, RET)
#define WRD_ARE_NULL(RET, ...)		NE_EACH_EXPAND(_ARE_NULL, RET, __VA_ARGS__)

#define WRD_IS_THIS_1(TYPE)			WRD_IS_NULL(*this, Nuller<Type>::ref)
#define WRD_IS_THIS_0()				WRD_IS_THIS_1(This)
#define WRD_IS_THIS ....

#define WRD_IS_CONST(RET)			\
	if((this->isConst())) {			\
		ConstCancel.warn(#RET);		\
		return RET;					\
	}

#define WRD_IS_ERR(STMT)			\
	{								\
		Result& res = (STMT);		\
		if(res)						\
			return res.err(#STMT);	\
	}
#define WRD_IS_WARN(STMT)			\
	{....

