#pragma once

#include "../NETList/NETList.hpp"
#include "../NEArgumentBase/NEArgumentBase.hpp"

namespace NE
{
	template
	class NE_DLL NETList<NEArgumentBase*, false>;
	typedef NETList<NEArgumentBase*> NEArgumentList;
}