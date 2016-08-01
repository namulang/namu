#pragma once

#include "../NETArray/NETArray.hpp"
#include "../NEClassBase/NEClassBase.hpp"

namespace NE
{
	template
	class NE_DLL NETArray<NEClassBase*, true>;
	typedef NETArray<NEClassBase*, true> NEClassBaseSet;
}