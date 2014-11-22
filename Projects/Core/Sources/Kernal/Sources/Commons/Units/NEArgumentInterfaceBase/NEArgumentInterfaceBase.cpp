#include "NEArgumentInterfaceBase.hpp"

namespace NE
{
	bool NE_DLL NEArgumentInterfaceBase::operator==(const NEArgumentInterfaceBase& rhs) const
	{
		return this == &rhs;
	}
}