#pragma once

#include "../NEPackage/NEPackage.hpp"
#include "../NETArray/NETArray.hpp"

namespace NE
{
	template
	class NE_DLL NETArray<NEPackage>;
	typedef NETArray<NEPackage> NEPackageSet;
}