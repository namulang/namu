///	@file	NE_OVERLOADER.hpp
///	@brief	Make it possible to provide overloaded macro.
///	@remark	These are codes inspired from Boost library. added the PATCH for VS.
#pragma once

///	Implementing Macro Overloding:
///		by count of given arguments, let compiler determine which macro should works.
///		code inspired by Boost library, patched for visual studio's weird varadic macro.
///
///		Varadic macro evalution hack for visual studio:
///			Different to other compiler, VS expand macro weirdly. varadic arguments 
///			would be evalutated	as single one piece after evaluated at least once.
#define _VS_EXP_HACK(...) __VA_ARGS__

//		make it count for arguments:
#define _ARGCOUNT(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, N, ...)	N
#define ARGCOUNT(...)	_VS_EXP_HACK(_ARGCOUNT(__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0))

//		branch to macro that would be expanded by its argument count:
#define _MACRO_OVERLOAD(macro_name, argcount)	macro_name##_##argcount
#define MACRO_OVERLOAD(macro_name, argcount)	_MACRO_OVERLOAD(macro_name, argcount)
#define NE_OVERLOADER(macro_name)	\
	#define	macro_name(...)		\
		MACRO_OVERLOAD(macro_name, ARGCOUNT(__VA_ARGS__))##(__VA_ARGS__)