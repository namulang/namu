//	Comments:	
//	Memo	:
//	Author	:	2016-02-27	kniz
//	---------------------------------------------------------------------------------

#pragma once

#include "../NEClassBase/NEClassBase.hpp"
#include "../NETList/NETList.hpp"

namespace NE
{
	template
	class NE_DLL NETList<NEClassBase*, true>;
	typedef NETList<NEClassBase*, true> NEClassBaseList;
}