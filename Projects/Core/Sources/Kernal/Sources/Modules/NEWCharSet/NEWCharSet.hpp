#pragma once

#pragma message("NEWCharSet.hpp - 1")
#include "../NETArray/NETArray.hpp"
#pragma message("NEWCharSet.hpp - 2")

namespace NE
{
	template
	class NE_DLL NETArray<type_wchar, false, type_wchar>;
	typedef NETArray<type_wchar, false, type_wchar> NEWCharSet;
}
#pragma message("NEWCharSet.hpp - 3")