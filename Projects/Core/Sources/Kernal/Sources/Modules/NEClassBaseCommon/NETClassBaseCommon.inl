namespace NE
{
	template <typename T>
	const NETString& NETClassBaseCommon<T>::getName() const
	{
		return getNameStatically();
	}

	template <typename T>
	const NEClassBaseList& NETClassBaseCommon<T>::getSuperClasses() const
	{
		return getSuperClassesStatically();
	}

	template <typename T>
	const NEClassBaseList& NETClassBaseCommon<T>::getSubClasses() const
	{
		return getSubClassesStatically();
	}

	template <typename T>
	const NETString& NETClassBaseCommon<T>::getNameStatically()
	{
		static NETString _inner;

		if (_inner.getLength() <= 0)
			_inner = typeid(T).name();

		return _inner;
	}

	template <typename T>
	const NEClassBase& NETClassBaseCommon<T>::getClass() const
	{
		return getClassStatically();
	}

	template <typename T>
	const NEClassBase& NETClassBaseCommon<T>::getClassStatically()
	{
		static NETClass<T> inner;

		return inner;
	}

	template <typename T>
	type_result NETClassBaseCommon<T>::_setIdentifier(const NEClassIdentifier& new_identifier)
	{
		NEClassIdentifier& casted = const_cast<NEClassIdentifier&>(getIdentifierStatically());

		casted = new_identifier;

		return RESULT_SUCCESS;
	}

	template <typename T>
	const NEClassIdentifier& NETClassBaseCommon<T>::getIdentifier() const
	{
		return getIdentifierStatically();
	}

	template <typename T>
	const NEClassIdentifier& NETClassBaseCommon<T>::getIdentifierStatically()
	{
		static NEClassIdentifier _inner;

		return _inner;
	}

	template <typename T>
	type_result NETClassBaseCommon<T>::_setRegistered(type_bool new_is_registered)
	{
		type_bool& is_registered = const_cast<type_bool&>(isRegisteredStatically());

		is_registered = new_is_registered;

		return RESULT_SUCCESS;
	}

	template <typename T>
	const type_bool& NETClassBaseCommon<T>::isRegisteredStatically()
	{
		static type_bool _inner;

		return _inner;
	}

	template <typename T>
	const NEClassBaseList& NETClassBaseCommon<T>::getSuperClassesStatically()
	{
		static NEClassBaseList _inner;

		return _inner;
	}
	template <typename T>
	const NEClassBaseList& NETClassBaseCommon<T>::getSubClassesStatically()
	{
		static NEClassBaseList _inner;

		return _inner;
	}
}