#pragma once

#include "NETConcreteClass.inl"
#include "../NETClassBase/NETClassBase.hpp"
namespace NE
{
	//	NETClass doesn't need to declare MetaClass Macro (like NE_DEFINE_CLASS_ONLY...):
	//		its class definitions are inherited from NETClassBase.
	template <typename T>
	NEObject& NETConcreteClass<T>::instantiate() const
	{
		if( ! isInstantiable())
			return Super::instantiate();

		return *(new T());
	}
}