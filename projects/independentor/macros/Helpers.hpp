#pragma once

//		helpers:
//			VS HACK for EXPanding macro:
//				Visual Studio's compiler expand macro weirdly. 
//				So in order to get output same as GCCed ones, we should wrap
//				varidic arguments once again.
//				
//				these just happen to TO_STR macro as same. That's why we are
//				define TO_STR with what looks like useless macro __TO_STR.
#define _VS_EXP_HACK(...) __VA_ARGS__
//			stringizer:
#define __WRD_TO_STR(x)	#x
#define WRD_TO_STR(x)	__WRD_TO_STR(x)

#define WRD_COMMA ,
#define WRD_VOID
#define WRD_SPACE WRD_VOID WRD_VOID
#define WRD_CONSUME_ARGS(...)
#define WRD_UNWRAP(...) __VA_ARGS__
