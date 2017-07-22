#pragma once

///	Varadic macro evalution hack for visual studio:
///		Different to other compiler, VS expand macro weirdly. varadic arguments 
///		would be evalutated	as single one piece after evaluated at least once.
#define NE_VS_EXP_HACK(...) __VA_ARGS__