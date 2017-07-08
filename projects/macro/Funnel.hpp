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
//			My_2(NE_MACRO_FUNNEL(MyMap<T, U>), NE_MACRO_FUNNEL(template <typename T, typename U))
#include "Overloader.hpp"

#define NE_MACRO_FUNNEL_2(X, Y)	X, Y
#define NE_MACRO_FUNNEL_3(X, Y, Z) NE_MACRO_FUNNEL_2(X, Y), Z
#define NE_MACRO_FUNNEL_4(X, Y, Z, A) NE_MACRO_FUNNEL_2(X, Y) , NE_MACRO_FUNNEL_2(Z, A)
#define NE_MACRO_FUNNEL(...)	NE_MACRO_OVERLOADER(NE_MACRO_FUNNEL, __VA_ARGS__)