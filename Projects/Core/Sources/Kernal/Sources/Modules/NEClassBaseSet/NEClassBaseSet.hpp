#pragma once

#include "../NETVector/NETVector.hpp"
#include "../NEClassBase/NEClassBase.hpp"
#include "../NETDeeper/NETDeeper.hpp"

namespace NE
{
	template
	class NE_DLL NETDeeper<NETVector<NEClassBase>>;
	typedef NETDeeper<NETVector<NEClassBase>> NEClassBaseSet;
}