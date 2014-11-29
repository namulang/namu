#include "NEArgumentInterfaceBase.hpp"
#include "../NEArgumentBase/NEArgumentBase.hpp"

namespace NE
{
	bool NE_DLL NEArgumentInterfaceBase::operator==(const NEArgumentInterfaceBase& rhs) const
	{
		return this == &rhs;
	}

	bool NE_DLL NEArgumentInterfaceBase::isValidToBind(const NEArgumentBase& arg) const	
	{	
		return arg.getTypeToBeBinded() == getKeyType();	
	}

	type_result NE_DLL NEArgumentInterfaceBase::isValid() const
	{
		return SuperClass::isValid();
	}	
}