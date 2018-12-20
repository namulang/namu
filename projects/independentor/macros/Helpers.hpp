#pragma once

//		helpers:
#define WRD_COMMA ,
#define WRD_VOID()
#define WRD_SPACE WRD_VOID WRD_VOID
#define WRD_CONSUME_ARGS(...)
#define WRD_UNWRAP(...) __VA_ARGS__

#define WRD_UNCONST_0()			WRD_UNCONST_1(unconst)
#define WRD_UNCONST_1(value)	This* value = const_cast<This*>(this);
#define WRD_UNCONST(...)		WRD_OVERLOAD(WRD_UNCONST, __VA_ARGS__)

