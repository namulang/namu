#pragma once

#include "Overload.hpp"

///	the macro for definining lazymethod which will be initialized when it's called.
//	this's uses static variable inside of method.
#define _LAZY_METHOD(ReturnType, Name, isConst, StaticType, initValue)	\
	isConst ReturnType Name() isConst { \
		static StaticType inner initValue; \
		return inner; \
	}
#define WRD_LAZY_METHOD_5(ReturnType, Name, isConst, StaticType, initValue) \
	_LAZY_METHOD(ReturnType, Name, isConst, StaticType, = initValue)
#define WRD_LAZY_METHOD_4(ReturnType, Name, isConst, StaticType) \
    _LAZY_METHOD(ReturnType, Name, isConst, StaticType, WRD_VOID())
#define WRD_LAZY_METHOD_3(StaticType, Name, isConst)  \
	_LAZY_METHOD(StaticType&, Name, isConst, StaticType, WRD_VOID())
#define WRD_LAZY_METHOD_2(StaticType, Name)	\
	_LAZY_METHOD(StaticType&, Name, WRD_SPACE, StaticType, WRD_VOID())
#define WRD_LAZY_METHOD(...)	WRD_OVERLOAD(WRD_LAZY_METHOD, __VA_ARGS__)
