namespace NE
{
	template <typename T>
	NEObject& NETUnknownMetaClass<T>::instantiate() const
	{
		NEObject* nullptr = 0x00;
		_alert(RESULT_TYPE_WARNING, "can't instantiate unknown class.");

		return *nullptr;
	}

	template <typename T>
	NEObject& NETUnknownMetaClass<T>::clone() const
	{
		return *(new This(*this));
	}
}