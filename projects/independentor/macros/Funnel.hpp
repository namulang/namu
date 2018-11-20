#pragma once

//	Funnel:
//		This macro mostly used to put in arguments to macro behind macro.
//
//		Why does we need this?:
//			#define My_2(X, Y) .......
//
//			But, if you put class template as macro argument, expanding macro gets messed up.
//				My_2(template<int, float>, template<A, B>) // in fact, preprocessor thought we 
//					passed 4 arguments, not 2.
//
//		Then, Use Funnel macro instead:
//			My_2(WRD_MACRO_FUNNEL(MyMap<T, U>), WRD_MACRO_FUNNEL(template <typename T, typename U))
#include "Overloader.hpp"

#define WRD_MACRO_FUNNEL_2(X, Y)	X, Y
#define WRD_MACRO_FUNNEL_3(X, Y, Z) WRD_MACRO_FUNNEL_2(X, Y), Z
#define WRD_MACRO_FUNNEL_4(X, Y, Z, A) WRD_MACRO_FUNNEL_2(X, Y) , WRD_MACRO_FUNNEL_2(Z, A)
#define WRD_MACRO_FUNNEL(...)	WRD_MACRO_OVERLOADER(WRD_MACRO_FUNNEL, __VA_ARGS__)
