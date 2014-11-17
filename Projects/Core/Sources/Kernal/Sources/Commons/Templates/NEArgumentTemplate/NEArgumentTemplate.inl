namespace NE
{
	template <typename T>
	NEArgumentTemplate<T>::NEArgumentTemplate() 
		: SuperClass(T().getType())
	{

	}

	template <typename T>
	NEArgumentTemplate<T>::NEArgumentTemplate(typename const T::Trait& default_value) 
		: SuperClass(T().getType()), _default(default_value)
	{

	}

	template <typename T>
	T& NEArgumentTemplate<T>::getBindedKey()
	{ 
		return static_cast<T&>(getBinded()); 
	}

	template <typename T>
	const T& NEArgumentTemplate<T>::getBindedKey() const
	{ 
		return static_cast<T&>(getBinded()); 
	}

	template <typename T>
	const T& NE::NEArgumentTemplate<T>::getDefaultKey() const
	{
		return _default;
	}

	template <typename T>
	T& NE::NEArgumentTemplate<T>::getDefaultKey()
	{
		return _default;
	}

	template <typename T>
	NEObject& NEArgumentTemplate<T>::clone() const
	{
		return *(new ThisClass(*this));
	}

	template <typename T>
	NEBinaryFileSaver& NEArgumentTemplate<T>::serialize(NEBinaryFileSaver& saver) const
	{
		SuperClass::serialize(saver);

		return saver << _default;
	}

	template <typename T>
	NEBinaryFileLoader& NEArgumentTemplate<T>::serialize(NEBinaryFileLoader& loader)
	{
		SuperClass::serialize(loader);

		return loader >> _default;
	}

	template <typename T>
	typename T::Trait& NE::NEArgumentTemplate<T>::getValue() 
	{
		if(isBinded())
		{
			NEKey& binded = getBinded();
			if(binded.getType() == getTypeToBeBinded())
				return getBindedKey().getValue();

			_default = binded;
		}

		return getDefault();
	}

	template <typename T>
	typename T::Trait& NE::NEArgumentTemplate<T>::getValue() const
	{
		if(isBinded())
		{
			NEKey& binded = getBinded();
			if(binded.getType() == getTypeToBeBinded())
				return getBindedKey();

			_default = binded;
			return getDefault();
		}
	}

	template <typename T>
	typename const T::Trait& NE::NEArgumentTemplate<T>::getDefault() const
	{
		return _default.getValue();
	}

	template <typename T>
	typename T::Trait& NE::NEArgumentTemplate<T>::getDefault()
	{
		return _default.getValue();
	}
}