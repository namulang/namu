#pragma once

#include "overload.hpp"

#define NAMU_DEF_ME_2(ME, SUPER) \
    NAMU_DEF_ME_1(NAMU_UNWRAP(ME)) \
    typedef NAMU_UNWRAP(SUPER) super;

#define NAMU_DEF_ME_1(ME) typedef NAMU_UNWRAP(ME) me;

#define NAMU_DEF_ME(...) NAMU_OVERLOAD(NAMU_DEF_ME, __VA_ARGS__)
