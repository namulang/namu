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
//			My_2(WRD_FUNNEL(MyMap<T, U>), WRD_FUNNEL(template <typename T, typename U))
#include "Overloader.hpp"

#define WRD_FUNNEL_2(X, Y)	X, Y
#define WRD_FUNNEL_3(X, Y, Z) WRD_FUNNEL_2(X, Y), Z
#define WRD_FUNNEL_4(X, Y, Z, A) WRD_FUNNEL_2(X, Y) , WRD_FUNNEL_2(Z, A)
#define WRD_FUNNEL(...)	WRD_OVERLOADER(WRD_FUNNEL, __VA_ARGS__)
