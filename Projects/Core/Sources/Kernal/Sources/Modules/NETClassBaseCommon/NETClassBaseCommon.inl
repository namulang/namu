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
	NEIdentifier& NETClassBaseCommon<T>::_getIdentifier()
	{
		NEIdentifier& casted = const_cast<NEIdentifier&>(getIdentifierStatically());

		return casted;
	}

	template <typename T>
	const NEIdentifier& NETClassBaseCommon<T>::getIdentifier() const
	{
		return getIdentifierStatically();
	}

	template <typename T>
	const NEIdentifier& NETClassBaseCommon<T>::getIdentifierStatically()
	{
		static NEIdentifier _inner;

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

	template <typename T>
	type_id NEClassBaseList& NETClassBaseCommon<T>::getId() const
	{
		return getIdStatically();
	}

	template <typename T>
	const type_id& NETClassBaseCommon<T>::getIdStatically()
	{
		static type_id _inner;

		return _inner;
	}

	template <typename T>
	type_result NETClassBaseCommon<T>::_setId(type_id new_id)
	{
		type_id& casted = const_cast<type_id&>(getIdStatically());

		casted = new_id;

		return RESULT_SUCCESS;
	}
}