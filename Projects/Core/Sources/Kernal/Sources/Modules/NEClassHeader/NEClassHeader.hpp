#pragma once

#include "../NEClassIdentifier/NEClassIdentifier.hpp"
#include "../NETHeader/NETHeader.hpp"

namespace NE
{
	template
	class NE_DLL NETHeader<NEClassIdentifier>;
	typedef NETHeader<NEClassIdentifier> NEClassIdentifier;
}