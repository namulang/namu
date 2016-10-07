#pragma once

#include "../NEPackage/NEPackage.hpp"
#include "../NETVector/NETVector.hpp"

namespace NE
{
	template
	class NE_DLL NETVector<NEPackage>;
	typedef NETVector<NEPackage> NEPackageSet;
}