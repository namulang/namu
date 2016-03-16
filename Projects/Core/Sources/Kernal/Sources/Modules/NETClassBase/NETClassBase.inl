namespace NE
{
	template <typename T>
	type_bool NETClassBase<T>::isMetaClassDefined() const
	{
		return IS_METACLASS_DEFINED;
	}

	template <typename T>
	type_bool NETClassBase<T>::isInstantiable() const
	{
		return IS_ADT;    //    Can't know because World check whether it's by MetaClass.
	}

	template <typename T>
	type_bool NETClassBase<T>::isTemplate() const
	{
		return IS_TEMPLATE;
	}

	template <typename T>
	type_bool NETClassBase<T>::isBuiltInClass() const
	{
		return IS_BUILT_IN_CLASS;
	}

	template <typename T>
	const type_bool& NETClassBase<T>::isRegistered() const
	{
		return isRegisteredStatically();
	}

	template <typename T>
	const NEClassBase& NETClassBase<T>::getTraitClass() const
	{
		return getTraitClassStatically();
	}

	template <typename T>
	const NEClassBaseList& NETClassBase<T>::getSubClasses() const
	{
		return getSubClassesStatically();
	}

	template <typename T>
	const NEClassBaseList& NETClassBase<T>::getSuperClasses() const
	{
		return getSuperClassesStatically();
	}

	template <typename T>
	const NETString& NETClassBase<T>::getName() const
	{
		return getNameStatically();
	}

	template <typename T>
	const NETString& NETClassBase<T>::getNameStatically()
	{
		static NETString _inner;

		if (_inner.getLength() <= 0)
			_inner = typeid(T).name();

		return _inner;
	}

	template <typename T>
	const NEClassBase& NETClassBase<T>::getTraitClassStatically()
	{
		static NETClass<Trait> _inner;

		return _inner;
	}

	template <typename T>
	type_result NETClassBase<T>::_setRegisteredStatically(type_bool new_is_registered)
	{
		type_bool& is_registered = const_cast<type_bool&>(isRegisteredStatically);

		is_registered = new_is_registered;

		return RESULT_SUCCESS;
	}

#define GENERATE_STATIC_METHOD(return_type, method_name)	\
	template <typename T>									\
	const return_type &NETClassBase<T>::method_name()		\
	{														\
	static return_type _inner;							\
	\
	return _inner;										\
	}
	GENERATE_STATIC_METHOD(type_bool, isRegisteredStatically)
		GENERATE_STATIC_METHOD(NEClassBaseList, getSuperClassesStatically)
		GENERATE_STATIC_METHOD(NEClassBaseList, getSubClassesStatically)
#undef GENERATE_STATIC_METHOD
}