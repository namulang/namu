#pragma once

#include "Overload.hpp"

///	the macro for definining lazymethod which will be initialized when it's called.
//	this's uses static variable inside of method.
#define _SINGLETON_GETTER(ReturnType, Name, isConst, StaticType, initValue)	\
	isConst ReturnType Name() isConst { \
		static StaticType inner initValue; \
		return inner; \
	}
#define WRD_SINGLETON_GETTER_5(ReturnType, Name, isConst, StaticType, initValue) \
	_SINGLETON_GETTER(ReturnType, Name, isConst, StaticType, = initValue)
#define WRD_SINGLETON_GETTER_4(ReturnType, Name, isConst, StaticType) \
    _SINGLETON_GETTER(ReturnType, Name, isConst, StaticType, WRD_VOID())
#define WRD_SINGLETON_GETTER_3(StaticType, Name, isConst)  \
	_SINGLETON_GETTER(StaticType&, Name, isConst, StaticType, WRD_VOID())
#define WRD_SINGLETON_GETTER_2(StaticType, Name)	\
	_SINGLETON_GETTER(StaticType&, Name, WRD_SPACE, StaticType, WRD_VOID())
#define WRD_SINGLETON_GETTER(...)	WRD_OVERLOAD(WRD_SINGLETON_GETTER, __VA_ARGS__)
