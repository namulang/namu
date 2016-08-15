#pragma once
#pragma warning(push)
#pragma warning(disable : 4800)
#pragma warning(disable : 4804)

//	include:
#include "../NETArithmeticKey/NETArithmeticKey.hpp"
#include "../../Commons/Units/NECode/NECode.hpp"

namespace NE
{
	template
	class NE_DLL NETArithmeticKey<NECode>;
	typedef NETArithmeticKey<NECode> NECodeKey;
}

#pragma warning(pop)