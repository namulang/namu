#pragma once

//        helpers:
#define NAMU_VOID()
#define NAMU_SPACE NAMU_VOID() NAMU_VOID()
#define NAMU_CONSUME_ARGS(...)
#define NAMU_UNWRAP(...) __VA_ARGS__

#define NAMU_UNCONST_0()             NAMU_UNCONST_1(unconst)
#define NAMU_UNCONST_1(value)        NAMU_UNCONST_2(me, value)
#define NAMU_UNCONST_2(type, value)  NAMU_UNWRAP(type)& value = *(const_cast<NAMU_UNWRAP(type)*>(this));
#define NAMU_UNCONST(...)            NAMU_OVERLOAD(NAMU_UNCONST, __VA_ARGS__)

#define NAMU_DELAY(x) x NAMU_VOID()

#define _STR(x)            #x
#define NAMU_STR(x)    _STR(x)

#define _CONCAT(x, y)    x##y
#define NAMU_CONCAT(x, y)    _CONCAT(x, y)

//    why delaying comma expressoin?:
//        it can causes delimiter issue on expanding macros for template parameters.
#define _COMMA() ,
#define NAMU_COMMA() NAMU_DELAY(_COMMA)()
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
