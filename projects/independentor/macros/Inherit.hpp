#pragma once

#include "Overload.hpp"

#define WRD_INHERIT_2(THIS, SUPER) 		\
		WRD_INHERIT_1(WRD_UNWRAP(THIS))	\
	public:								\
		typedef WRD_UNWRAP(SUPER) Super;\
	private:
#define WRD_INHERIT_1(THIS)				\
	public:								\
		typedef WRD_UNWRAP(THIS) This;	\
	private:
#define WRD_INHERIT(...)				WRD_OVERLOAD(WRD_INHERIT, __VA_ARGS__)
