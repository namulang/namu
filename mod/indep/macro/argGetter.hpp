#pragma once

//      argument getter:
//          this macro can pick designated indexing argument among varidics.
//
//          VARG2?:
//              NAMU_GET_VARG2_... are created for assuming varidic arguments
//              are paired. for instance,
//
//                  MyMacro(int, value1, float, value2, char, value3, double, value4...)
//
//              As you can see, even the macro can't distinguish whether those macro
//              arguments are a set of two, macro developer's want to.
//              Might can be used in this situation.
//
//              usage:
//                  VARG2 macro assumes that your macro's arguments were paired with
//                  two arguments as one. like,
//
//                      MyMacro(  int, value1,     float, value2,     char, value3...
//                                X_1    Y_1        X_2    Y_2         X_3    Y_3
//                  so, at example above, NAMU_GET_VARG2_X_2 will be substitued
//                  to 'float'.
//
//      argument getter defines:
//          Yeah, I know. This is looks somewhat stupid.
//          if you have better idea, please let me know. I beg you.
#define NAMU_GET_VARG_1(_1, ...) _1
#define NAMU_GET_VARG_2(_1, _2, ...) _2
#define NAMU_GET_VARG_3(_1, _2, _3, ...) _3
#define NAMU_GET_VARG_4(_1, _2, _3, _4, ...) _4
#define NAMU_GET_VARG_5(_1, _2, _3, _4, _5, ...) _5
#define NAMU_GET_VARG_6(_1, _2, _3, _4, _5, _6, ...) _6
#define NAMU_GET_VARG_7(_1, _2, _3, _4, _5, _6, _7, ...) _7
#define NAMU_GET_VARG_8(_1, _2, _3, _4, _5, _6, _7, _8, ...) _8
#define NAMU_GET_VARG_9(_1, _2, _3, _4, _5, _6, _7, _8, _9, ...) _9
#define NAMU_GET_VARG_10(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, ...) _10
#define NAMU_GET_VARG_11(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, ...) _11
#define NAMU_GET_VARG_12(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, ...) _12
#define NAMU_GET_VARG_13(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, ...) _13
#define NAMU_GET_VARG_14(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, ...) _14
#define NAMU_GET_VARG_15(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, ...) _15
#define NAMU_GET_VARG_16(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, ...) _16
#define NAMU_GET_VARG_17(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, ...) _17
#define NAMU_GET_VARG_18(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, ...) _18
#define NAMU_GET_VARG_19(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17,_18, _19, ...) _19
#define NAMU_GET_VARG_20(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17,_18, _19, _20, ...) _20
#define NAMU_GET_VARG_21(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17,_18, _19, _20, _21, ...) _21
#define NAMU_GET_VARG_22(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17,_18, _19, _20, _21, _22, ...) _22
#define NAMU_GET_VARG_23(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17,_18, _19, _20, _21, _22, _23, ...) _23
#define NAMU_GET_VARG_24(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17,_18, _19, _20, _21, _22, _23, _24, ...) _24
#define NAMU_GET_VARG_25(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17,_18, _19, _20, _21, _22, _23, _24, _25, ...) _25
#define NAMU_GET_VARG_26(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17,_18, _19, _20, _21, _22, _23, _24, _25, _26, ...) _26
#define NAMU_GET_VARG_27(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17,_18, _19, _20, _21, _22, _23, _24, _25, _26, _27, ...) _27
#define NAMU_GET_VARG_28(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17,_18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, ...) _28
#define NAMU_GET_VARG_29(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17,_18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, ...) _29
#define NAMU_GET_VARG_30(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17,_18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, ...) _30
#define NAMU_GET_VARG_31(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17,_18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, ...) _31
#define NAMU_GET_VARG_32(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17,_18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, ...) _32

#define NAMU_GET_VARG2_X_1(_1, _2, ...) _1
#define NAMU_GET_VARG2_X_2(_1, _2, _3, _4, ...) _3
#define NAMU_GET_VARG2_X_3(_1, _2, _3, _4, _5, _6, ...) _5
#define NAMU_GET_VARG2_X_4(_1, _2, _3, _4, _5, _6, _7, _8, ...) _7
#define NAMU_GET_VARG2_X_5(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, ...) _9
#define NAMU_GET_VARG2_X_6(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, ...) _11
#define NAMU_GET_VARG2_X_7(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, ...) _13
#define NAMU_GET_VARG2_X_8(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, ...) _15
#define NAMU_GET_VARG2_X_9(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, ...) _17
#define NAMU_GET_VARG2_X_10(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, ...) _19
#define NAMU_GET_VARG2_X_11(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, ...) _21
#define NAMU_GET_VARG2_X_12(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, ...) _23
#define NAMU_GET_VARG2_X_13(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, ...) _25
#define NAMU_GET_VARG2_X_14(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, ...) _27
#define NAMU_GET_VARG2_X_15(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, ...) _29
#define NAMU_GET_VARG2_X_16(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, ...) _31

#define NAMU_GET_VARG2_Y_1(_1, _2, ...) _2
#define NAMU_GET_VARG2_Y_2(_1, _2, _3, _4, ...) _5
#define NAMU_GET_VARG2_Y_3(_1, _2, _3, _4, _5, _6, ...) _6
#define NAMU_GET_VARG2_Y_4(_1, _2, c, _4, _5, _6, _7, _8, ...) _8
#define NAMU_GET_VARG2_Y_5(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, ...) _10
#define NAMU_GET_VARG2_Y_6(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, ...) _12
#define NAMU_GET_VARG2_Y_7(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, ...) _14
#define NAMU_GET_VARG2_Y_8(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, ...) _16
#define NAMU_GET_VARG2_Y_9(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, ...) _18
#define NAMU_GET_VARG2_Y_10(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, ...) _20
#define NAMU_GET_VARG2_Y_11(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, ...) _22
#define NAMU_GET_VARG2_Y_12(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, ...) _24
#define NAMU_GET_VARG2_Y_13(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, ...) _26
#define NAMU_GET_VARG2_Y_14(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, ...) _28
#define NAMU_GET_VARG2_Y_15(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, ...) _30
#define NAMU_GET_VARG2_Y_16(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, ...) _32
