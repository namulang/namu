#pragma once

#include "Overload.hpp"

#define WRD_DECL_THIS_2(THIS, SUPER) 		\
		WRD_DECL_THIS_1(WRD_UNWRAP(THIS))	\
	public:								\
		typedef WRD_UNWRAP(SUPER) Super;\
	private:
#define WRD_DECL_THIS_1(THIS)				\
	public:								\
		typedef WRD_UNWRAP(THIS) This;	\
	private:
#define WRD_DECL_THIS(...)				WRD_OVERLOAD(WRD_DECL_THIS, __VA_ARGS__)
