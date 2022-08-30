#pragma once

#include "overload.hpp"

#define __NAMU__DECL_DEF_ME_2(ME, SUPER) \
    __NAMU__DECL_DEF_ME_1(NAMU_UNWRAP(ME)) \
    typedef NAMU_UNWRAP(SUPER) super;

#define __NAMU__DECL_DEF_ME_1(ME) typedef NAMU_UNWRAP(ME) me;

#define __NAMU__DECL_DEF_ME(...) NAMU_OVERLOAD(NAMU_DEF_ME, __VA_ARGS__)

#define NAMU_DEF_ME_2(ME, SUPER) __NAMU__DECL_DEF_ME_2(ME, SUPER)
#define NAMU_DEF_ME_1(ME) __NAMU__DECL_DEF_ME_1(ME)
#define NAMU_DEF_ME(...) NAMU_OVERLOAD(NAMU_DEF_ME, __VA_ARGS__)
