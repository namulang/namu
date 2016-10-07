#pragma once

#include "../NETVector/NETVector.hpp"
#include "../NEClassBase/NEClassBase.hpp"

namespace NE
{
	template
	class NE_DLL NETVector<NEClassBase*, true>;
	typedef NETVector<NEClassBase*, true> NEClassBaseSet;
}