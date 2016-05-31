#pragma once

#include "../MacroOverloader/MacroOverloader.hpp"

//		for-each:
//			litererly, it's for-each of macro version.
//			there are 2 for-each by how you treat your arguments.
//				- FOR_EACH:	extract single argument at each time from varidics.
//				- FOR_EACH2: extract 2 args.
//
//			usage:
//				// define macro:
//				#define MyEach(x) cout << x << "\n";
//
//				// using:
//				NE_MACRO_FOR_EACH(MyEach, 1, 2, 3, 4, "hello world")
//
//				will be expanded to:
//					cout << 1 << "\n";
//					cout << 2 << "\n";
//					cout << 3 << "\n";
//					cout << 4 << "\n";
//					cout << "hello world" << "\n";
//
//				so, output should be:
//					1
//					2
//					3
//					4
//					hello world
#define NE_MACRO_FOR_EACH(...)	NE_MACRO_OVERLOADER(NE_MACRO_FOR_EACH, __VA_ARGS__)
#define NE_MACRO_FOR_EACH_2(METHOD, _1)	\
	METHOD(_1)
#define NE_MACRO_FOR_EACH_3(METHOD, _1, _2)	\
	NE_MACRO_FOR_EACH_2(METHOD, _1)			\
	METHOD(_2)
#define NE_MACRO_FOR_EACH_4(METHOD, _1, _2, _3)	\
	NE_MACRO_FOR_EACH_3(METHOD, _1, _2)			\
	METHOD(_3)
#define NE_MACRO_FOR_EACH_5(METHOD, _1, _2, _3, _4)	\
	NE_MACRO_FOR_EACH_4(METHOD, _1, _2, _3)			\
	METHOD(_4)
#define NE_MACRO_FOR_EACH_6(METHOD, _1, _2, _3, _4, _5)	\
	NE_MACRO_FOR_EACH_5(METHOD, _1, _2, _3, _4)			\
	METHOD(_5)
#define NE_MACRO_FOR_EACH_7(METHOD, _1, _2, _3, _4, _5, _6)	\
	NE_MACRO_FOR_EACH_6(METHOD, _1, _2, _3, _4, _5)			\
	METHOD(_6)
#define NE_MACRO_FOR_EACH_8(METHOD, _1, _2, _3, _4, _5, _6, _7)	\
	NE_MACRO_FOR_EACH_7(METHOD, _1, _2, _3, _4, _5, _6)			\
	METHOD(_7)
#define NE_MACRO_FOR_EACH_9(METHOD, _1, _2, _3, _4, _5, _6, _7, _8)	\
	NE_MACRO_FOR_EACH_8(METHOD, _1, _2, _3, _4, _5, _6, _7)			\
	METHOD(_8)
#define NE_MACRO_FOR_EACH_10(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9)	\
	NE_MACRO_FOR_EACH_9(METHOD, _1, _2, _3, _4, _5, _6, _7, _8)			\
	METHOD(_9)
#define NE_MACRO_FOR_EACH_11(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10)	\
	NE_MACRO_FOR_EACH_10(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9)			\
	METHOD(_10)
#define NE_MACRO_FOR_EACH_12(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11)	\
	NE_MACRO_FOR_EACH_11(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10)			\
	METHOD(_11)
#define NE_MACRO_FOR_EACH_13(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12)	\
	NE_MACRO_FOR_EACH_12(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11)			\
	METHOD(_12)
#define NE_MACRO_FOR_EACH_14(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13)	\
	NE_MACRO_FOR_EACH_13(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12)			\
	METHOD(_13)
#define NE_MACRO_FOR_EACH_15(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14)	\
	NE_MACRO_FOR_EACH_14(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13)			\
	METHOD(_14)
#define NE_MACRO_FOR_EACH_16(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15)	\
	NE_MACRO_FOR_EACH_15(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14)			\
	METHOD(_15)
#define NE_MACRO_FOR_EACH_17(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16)	\
	NE_MACRO_FOR_EACH_16(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15)			\
	METHOD(_16)
#define NE_MACRO_FOR_EACH_18(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17)	\
	NE_MACRO_FOR_EACH_17(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16)			\
	METHOD(_17)
#define NE_MACRO_FOR_EACH_19(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18)	\
	NE_MACRO_FOR_EACH_18(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17)			\
	METHOD(_18)
#define NE_MACRO_FOR_EACH_20(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19)	\
	NE_MACRO_FOR_EACH_19(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18)				\
	METHOD(_19)
#define NE_MACRO_FOR_EACH_21(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20)	\
	NE_MACRO_FOR_EACH_20(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19)				\
	METHOD(_20)
#define NE_MACRO_FOR_EACH_22(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21)	\
	NE_MACRO_FOR_EACH_21(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20)			\
	METHOD(_21)
#define NE_MACRO_FOR_EACH_23(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22)	\
	NE_MACRO_FOR_EACH_22(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21)			\
	METHOD(_22)
#define NE_MACRO_FOR_EACH_24(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23)	\
	NE_MACRO_FOR_EACH_23(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22)				\
	METHOD(_23)
#define NE_MACRO_FOR_EACH_25(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24)	\
	NE_MACRO_FOR_EACH_24(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23)				\
	METHOD(_24)
#define NE_MACRO_FOR_EACH_26(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25)	\
	NE_MACRO_FOR_EACH_25(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24)			\
	METHOD(_25)
#define NE_MACRO_FOR_EACH_27(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26)	\
	NE_MACRO_FOR_EACH_26(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25)			\
	METHOD(_26)
#define NE_MACRO_FOR_EACH_28(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27)	\
	NE_MACRO_FOR_EACH_27(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26)			\
	METHOD(_27)
#define NE_MACRO_FOR_EACH_29(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28)	\
	NE_MACRO_FOR_EACH_28(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27)			\
	METHOD(_28)
#define NE_MACRO_FOR_EACH_30(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29)	\
	NE_MACRO_FOR_EACH_29(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28)			\
	METHOD(_29)
#define NE_MACRO_FOR_EACH_31(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30)	\
	NE_MACRO_FOR_EACH_30(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29)			\
	METHOD(_30)
#define NE_MACRO_FOR_EACH_32(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31)	\
	NE_MACRO_FOR_EACH_31(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30)				\
	METHOD(_31)

//		FOR_EACH2:
//			just same as FOR_EACH except that this extract 2 arguments at
//			each time.
//
//			usage:
//				// define macro:
//				#define MyEach(x, y) cout << (x)+(y) << "\n";
//
//				// using:
//				NE_MACRO_FOR_EACH2(MyEach, 1, 2, 3, 4)
//
//				will be expanded to:
//					cout << (1)+(2) << "\n";
//					cout << (3)+(4) << "\n";
//
//				so, output should be:
//					3
//					7
#define NE_MACRO_FOR_EACH2(...)	NE_MACRO_OVERLOADER(NE_MACRO_FOR_EACH2, __VA_ARGS__)
#define NE_MACRO_FOR_EACH2_3(METHOD, _1, _2)	\
	METHOD(_1, _2)
#define NE_MACRO_FOR_EACH2_5(METHOD, _1, _2, _3, _4)	\
	NE_MACRO_FOR_EACH2_3(METHOD, _1, _2)				\
	METHOD(_3, _4)
#define NE_MACRO_FOR_EACH2_7(METHOD, _1, _2, _3, _4, _5, _6)	\
	NE_MACRO_FOR_EACH2_5(METHOD, _1, _2, _3, _4)				\
	METHOD(_5, _6)
#define NE_MACRO_FOR_EACH2_9(METHOD, _1, _2, _3, _4, _5, _6, _7, _8)	\
	NE_MACRO_FOR_EACH2_7(METHOD, _1, _2, _3, _4, _5, _6)				\
	METHOD(_7, _8)
#define NE_MACRO_FOR_EACH2_11(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10)	\
	NE_MACRO_FOR_EACH2_9(METHOD, _1, _2, _3, _4, _5, _6, _7, _8)					\
	METHOD(_9, _10)
#define NE_MACRO_FOR_EACH2_13(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12)	\
	NE_MACRO_FOR_EACH2_11(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10)				\
	METHOD(_11, _12)
#define NE_MACRO_FOR_EACH2_15(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14)	\
	NE_MACRO_FOR_EACH2_13(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12)					\
	METHOD(_13, _14)
#define NE_MACRO_FOR_EACH2_17(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16)	\
	NE_MACRO_FOR_EACH2_15(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14)				\
	METHOD(_15, _16)
#define NE_MACRO_FOR_EACH2_19(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18)	\
	NE_MACRO_FOR_EACH2_17(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16)					\
	METHOD(_17, _18)
#define NE_MACRO_FOR_EACH2_21(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20)	\
	NE_MACRO_FOR_EACH2_19(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18)				\
	METHOD(_19, _20)
#define NE_MACRO_FOR_EACH2_23(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22)	\
	NE_MACRO_FOR_EACH2_21(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20)					\
	METHOD(_21, _22)
#define NE_MACRO_FOR_EACH2_25(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24)	\
	NE_MACRO_FOR_EACH2_23(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22)				\
	METHOD(_23, _24)
#define NE_MACRO_FOR_EACH2_27(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26)	\
	NE_MACRO_FOR_EACH2_25(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24)					\
	METHOD(_25, _26)
#define NE_MACRO_FOR_EACH2_29(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28)	\
	NE_MACRO_FOR_EACH2_27(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26)				\
	METHOD(_27, _28)
#define NE_MACRO_FOR_EACH2_31(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30)	\
	NE_MACRO_FOR_EACH2_29(METHOD, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28)					\
	METHOD(_29, _30)