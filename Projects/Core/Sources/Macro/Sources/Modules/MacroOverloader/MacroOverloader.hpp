///	@file	MacroOverloader
///	@brief	Make it possible to overide specified macro.

#include "../ArgumentCounter/ArgumentCounter.hpp"

//	macro:
//		overloader:
//			Inspired by boost codes.
//			branching macros would be choosed by its argument count.
//			
//			usage:
//				//	define macro:
//				#define MyMacro_1(x) (x)+5
//				#define MyMacro_2(x, y) (x)+(y)
//				#define MyMacro(...)	NE_MACRO_OVERLOADER(MyMacro, __VA_ARGS__)
//
//				//	using:
//				cout << MyMacro(5) << ", " << MyMacro(3, 5) << "\n";
//
//			output:
//				10, 8
#define ___NE_MACRO_OVERLOADER(macro_name, argcount)	macro_name##_##argcount
#define __NE_MACRO_OVERLOADER(macro_name, argcount)	___NE_MACRO_OVERLOADER(macro_name, argcount)
#define NE_MACRO_OVERLOADER(macro_name, ...)	\
	__NE_MACRO_OVERLOADER(macro_name, NE_MACRO_ARGCOUNT(__VA_ARGS__))##(__VA_ARGS__)