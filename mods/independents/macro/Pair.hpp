#pragma once

//	Funnel:
//		This macro mostly used to put in arguments to macro behind macro.
//
//		Why does we need this?:
//			#define My_2(X, y) .......
//
//			But, if you put class template as macro argument, expanding macro gets messed up.
//				My_2(template<int, float>, template<A, B>) // in fact, preprocessor thought we 
//					passed 4 arguments, not 2.
//
//		Then, Use Funnel macro instead:
//			My_2(WRD_PAIR(MyMap<T, U>), WRD_PAIR(template <typename T, typename U))
#include "Helper.hpp"
#include "Overload.hpp"

#define WRD_PAIR_1(x)			x
#define WRD_PAIR_2(x, y)		x, y
#define WRD_PAIR_3(x, y, z) 	WRD_PAIR_2(x, y), z
#define WRD_PAIR_4(x, y, z, a) 	WRD_PAIR_2(x, y) , WRD_PAIR_2(z, a)
#define WRD_PAIR(...)			WRD_OVERLOAD(WRD_PAIR, __VA_ARGS__)
