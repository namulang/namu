#pragma once

#include "NETUnknownMetaClass.inl"
#include "../NETClassBase/NETClassBase.hpp"

namespace NE
{
	//	NETClass doesn't need to declare MetaClass Macro (like NE_DEFINE_CLASS_ONLY...):
	//		its class definitions are inherited from NETClassBase.

	template <typename T>
	NEObject& NETUnknownMetaClass<T>::instantiate() const
	{
		NEObject* nullptr = 0x00;
		_alert(RESULT_TYPE_WARNING, _T("can't instantiate unknown class."));

		return *nullptr;
	}
}