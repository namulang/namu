#pragma once

#include "defThis.hpp"

#define NAMU_ME_2(ME, SUPER) \
    public: \
        NAMU_DEF_ME_2(ME, SUPER) \
    private:

#define NAMU_ME_1(ME) \
    public: \
        NAMU_DEF_ME_1(ME) \
    private:

#define NAMU_ME(...)  NAMU_OVERLOAD(NAMU_ME, __VA_ARGS__)

// namuMeta macro's sub-commands:
//  ME: actually it redirects builtin macro 'NAMU_ME'.
#define __NAMU__DECL_ME_1(ME) NAMU_ME_1(ME)
#define __NAMU__DECL_ME_2(ME, SUPER) NAMU_ME_2(ME, SUPER)
#define __NAMU__DECL_ME(...) NAMU_OVERLOAD(__NAMU__DECL_ME, __VA_ARGS__)