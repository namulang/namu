//	Comments:	
//	Memo	:
//	Author	:	2016-02-27	kniz
//	---------------------------------------------------------------------------------

#pragma once

#include "../NEClassBase/NEClassBase.hpp"
#include "../NETList/NETList.hpp"
#include "../NETDeeper/NETDeeper.hpp"

namespace NE
{
	template
	class NE_DLL NETDeeper<NETList<NEClassBase>>;
	typedef NETDeeper<NETList<NEClassBase>> NEClassBaseList;
}