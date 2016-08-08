#pragma once

#include "../../NETClass/NETClass.hpp"

//	TBD....TBD....TBD....TBD....TBD....TBD....TBD....TBD....
#define NE_DECLARE_MODULE_5(A, B, C, D, E)	public: private:
#define NE_DECLARE_MODULE_2(THIS, SUPER)	public: private:
#define NE_DECLARE_MODULE(...) NE_MACRO_OVERLOADER(NE_DECLARE_MODULE, __VA_ARGS__)