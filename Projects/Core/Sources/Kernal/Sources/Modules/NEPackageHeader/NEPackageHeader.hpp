#pragma once

#include "../NETHeader/NETHeader.hpp"
#include "../NEIdentifier/NEIdentifier.hpp"

namespace NE
{
	template
	class NE_DLL NETHeader<NEIdentifier>;
	typedef NETHeader<NEIdentifier> NEPackageHeader;
}