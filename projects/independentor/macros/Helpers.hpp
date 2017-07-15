#pragma once

//		helpers:
//			VS HACK for EXPanding macro:
//				Visual Studio's compiler expand macro weirdly. 
//				So in order to get output same as GCCed ones, we should wrap
//				varidic arguments once again.
//				
//				these just happen to STRINGIZER macro as same. That's why we are
//				define STRINGIZER with what looks like useless macro __STRINGIZER.
#define _VS_EXP_HACK(...) __VA_ARGS__
//			concatenate:
#define NE_MACRO_CONCATENATE(x, y) x##y
//			stringizer:
#define __NE_MACRO_STRINGIZER(x)	#x
#define NE_MACRO_STRINGIZER(x)	__NE_MACRO_STRINGIZER(x)