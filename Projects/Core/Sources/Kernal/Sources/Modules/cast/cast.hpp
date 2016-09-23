#pragma once

#include "../NETDerviedClassChecker/NETDerviedClassChecker.hpp"
#include "../NEObject.hpp"

namespace NE
{
	template <typename T>
	T& cast(Object& adt) 
	{
		T* nullpointer = 0x00;

		return	adt.isSubClassOf(T::getClassStatically()) ? 
				(T&) adt : *nullpointer;
	}
}