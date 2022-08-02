#pragma once

//    Funnel:
//        This macro mostly used to put in arguments to macro behind macro.
//
//        Why does we need this?:
//            #define My_2(X, y) .......
//
//            But, if you put class template as macro argument, expanding macro gets messed up.
//                My_2(template<int, float>, template<A, B>) // in fact, preprocessor thought we 
//                    passed 4 arguments, not 2.
//
//        Then, Use Funnel macro instead:
//            My_2(NAMU_PAIR(MyMap<T, U>), NAMU_PAIR(template <typename T, typename U))
#include "helper.hpp"
#include "overload.hpp"

#define NAMU_PAIR_1(x)           x
#define NAMU_PAIR_2(x, y)        x, y
#define NAMU_PAIR_3(x, y, z)     NAMU_PAIR_2(x, y), z
#define NAMU_PAIR_4(x, y, z, a)  NAMU_PAIR_2(x, y) , NAMU_PAIR_2(z, a)
#define NAMU_PAIR(...)           NAMU_OVERLOAD(NAMU_PAIR, __VA_ARGS__)
