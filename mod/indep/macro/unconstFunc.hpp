#pragma once

#include "overload.hpp"

#define NAMU_UNCONST_FUNC_2(type, funcCall) { \
        type* uncThis = const_cast<type*>(this); \
        return uncThis->funcCall; \
    }
#define NAMU_UNCONST_FUNC_1(funcCall) NAMU_UNCONST_FUNC_2(me, funcCall);
#define NAMU_UNCONST_FUNC(...) NAMU_OVERLOAD(NAMU_UNCONST_FUNC, __VA_ARGS__)
