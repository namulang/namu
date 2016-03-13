namespace NE
{
	template <typename T>
	NEObject& NE::NETConcreteClass<T>::instantiate() const
	{
		if( ! isInstantiatable())
		{
			_alert(RESULT_TYPE_INFORMATION, 
				_T("This class is a kind of Object class, But can't instantiate."));

			NEObject* nullptr = 0x00;

			return *nullptr;
		}

		return *(new Trait());
	}

	template <typename T>
	const NEClassBase& getClassStatically()
	{
		static MetaClass _inner;

		return _inner;
	}
}