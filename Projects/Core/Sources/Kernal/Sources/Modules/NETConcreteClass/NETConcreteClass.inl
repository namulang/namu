namespace NE
{
	template <typename T>
	NEObject& NETConcreteClass<T>::instantiate() const
	{
		if( ! isInstantiable())
		{
			_alert(RESULT_TYPE_INFORMATION, 
				_T("This class is a kind of Object class, But can't instantiate."));

			NEObject* nullptr = 0x00;

			return *nullptr;
		}

		return *(new T());
	}

	template <typename T>
	NEObject& NETConcreteClass<T>::clone() const
	{
		return *(new This(*this));
	}
}