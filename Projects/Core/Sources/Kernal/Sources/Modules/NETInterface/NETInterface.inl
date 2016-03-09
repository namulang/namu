namespace NE
{
	template <typename T>
	NETInterface<T>::~NETInterface()
	{

	}

	template <typename T>
	NETInterface<T>::NETInterface(const NETInterface& source)
		: NEClassBase(source)
	{

	}

	template <typename T>
	NETInterface<T>::NETInterface()
		: NEClassBase()
	{

	}

	template <typename T>
	NEObject& NETInterface<T>::clone() const
	{
		return *(new This(*this));
	}

	template <typename T>
	NEObject& NETInterface<T>::instantiate() const
	{
		NEObject* nullptr = 0x00;
		_alert(RESULT_TYPE_WARNING, _T("You can't instantiate interface class."));

		return *nullptr;
	}

	template <typename T>
	type_bool NE::NETInterface<T>::isInstantiatable() const
	{
		return false;
	}

	template <typename T>
	const NEClassBaseList& NETInterface<T>::getSubClasses() const
	{
		return getSubClassesStatically();
	}

	template <typename T>
	const bool& NETInterface<T>::isRegistered() const
	{
		return isRegisteredStatically();
	}

	template <typename T>
	const NEClassBaseList& NETInterface<T>::getSuperClasses() const
	{
		return getSuperClassesStatically();
	}

	template <typename T>
	const NETString& NETInterface<T>::getName() const
	{
		return getNameStatically();
	}

	template <typename T>
	const NETString& getNameStatically()
	{
		static NEString _inner;

		if(_inner.getLength() <= 0)
			_inner = typeid(T).name();

		return _inner;
	}

	template <typename T>
	const NEClassBase& NE::NETInterface<T>::getClass() const
	{
		return getClassStatically();
	}


	template <typename T>
	const NEClassBase& NETInterface<T>::getClassStatically()
	{
		static ThisClass _inner;

		return _inner;
	}

#define GENERATE_STATIC_METHOD(return_type, method_name)	\
	template <typename T>									\
	const return_type &NETInterface<T>::method_name()		\
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