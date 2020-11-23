#pragma once

#include "DefThis.hpp"

#define WRD_DECL_THIS_2(THIS, SUPER) \
	public:	\
        WRD_DEF_THIS_2(THIS, SUPER) \
	private:

#define WRD_DECL_THIS_1(THIS) \
	public:	\
        WRD_DEF_THIS_1(THIS) \
	private:

#define WRD_DECL_THIS(...)  WRD_OVERLOAD(WRD_DECL_THIS, __VA_ARGS__)
