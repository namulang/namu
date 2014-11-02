#include "NEArgumentInterfaceBase.hpp"

namespace NE
{
	bool NEArgumentInterfaceBase::operator==(const NEArgumentInterfaceBase& rhs) const
	{
		return this == &rhs;
	}
}