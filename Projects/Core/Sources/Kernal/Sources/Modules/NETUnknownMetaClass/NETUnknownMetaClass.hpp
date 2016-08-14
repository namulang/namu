#include "NETUnknownMetaClass.inl"
#include "../NETClassBase/NETClassBase.hpp"

namespace NE
{
	NE_DEFINE_CLASS_ONLY(NETUnknownMetaClass<T>)

	template <typename T>
	NEObject& NETUnknownMetaClass<T>::instantiate() const
	{
		NEObject* nullptr = 0x00;
		_alert(RESULT_TYPE_WARNING, _T("can't instantiate unknown class."));

		return *nullptr;
	}
}