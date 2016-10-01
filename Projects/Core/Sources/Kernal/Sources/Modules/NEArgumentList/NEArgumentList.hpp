#pragma once

#include "../NETList/NETList.hpp"
#include "../NETDeeper/NETDeeper.hpp"
#include "../NEArgumentBase/NEArgumentBase.hpp"

namespace NE
{
	template
	class NE_DLL NETDeeper<NETList<NEArgumentBase>>;
	typedef NETDeeper<NETList<NEArgumentBase>> NEArgumentList;
}