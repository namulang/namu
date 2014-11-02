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
			return getBindedKey().getValue();
		else
			return _default.getValue();
	}

	template <typename T>
	const T& NE::NEArgumentTemplate<T>::getDefault() const
	{
		return _default;
	}

	template <typename T>
	T& NE::NEArgumentTemplate<T>::getDefault()
	{
		return _default;
	}

	template <typename T>
	type_result NE::NEArgumentTemplate<T>::bind()
	{
		if(isBinded())	return RESULT_SUCCESS | RESULT_ABORT_ACTION;

		type_result result = SuperClass::bind();
		if( NEResult::hasError(result)						||	
			! getBinded().isSubClassOf(getTypeToBeBinded())	)
			return RESULT_TYPE_ERROR | result;

		return result;
	}
}