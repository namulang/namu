#pragma once

//	Funnel:
//		This macro mostly used to put in arguments to macro behind macro.
//
//		Exmaple:
//			#define My_2(X, Y) .......
//
//			But, if you put template as argument, expanding macro gets messed up.
//				My_2(template<int, float>, template<A, B>) // this actually is expanded to 3 arguments.
//
//
//			use Funnel macro instead of.
//				#define My_4(A, B, C, D) My_2(NE_MACRO_FUNNEL(A, B), NE_MACRO_FUNNEL(C, D))
//				#define My NE_MACRO_OVERLOADER(My, __VA_ARGS__)
//
//				My(template<int, float>, template<A, B>) // this will be expanded as like My_4 first, and it works.

#include "../OverloaderMacro/OverloaderMacro.hpp"

#define NE_MACRO_FUNNEL_2(X, Y)	X, Y
#define NE_MACRO_FUNNEL_3(X, Y, Z) NE_MACRO_FUNNEL_2(X, Y), Z
#define NE_MACRO_FUNNEL_4(X, Y, Z, A) NE_MACRO_FUNNEL_2(X, Y) , NE_MACRO_FUNNEL_2(Z, A)
#define NE_MACRO_FUNNEL(...)	NE_MACRO_OVERLOADER(NE_MACRO_FUNNEL, __VA_ARGS__)
