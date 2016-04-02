#pragma once

#include "../NEPackage/NEPackage.hpp"
#include "../NETList/NETList.hpp"

namespace NE
{
	template
	class NE_DLL NETList<NEPackage>;
	typedef NETList<NEPackage> NEPackageList;
}