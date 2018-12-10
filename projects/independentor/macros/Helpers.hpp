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
#define WRD_CONCATENATE(x, y) x##y
//			stringizer:
#define __WRD_STRINGIZER(x)	#x
#define WRD_STRINGIZER(x)	__WRD_STRINGIZER(x)

#define WRD_COMMA ,
#define WRD_VOID
#define WRD_SPACE WRD_VOID WRD_VOID
#define WRD_CONSUME_ARGS(...)
#define WRD_UNWRAP(...) __VA_ARGS__
