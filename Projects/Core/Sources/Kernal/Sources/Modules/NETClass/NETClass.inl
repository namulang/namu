namespace NE
{
	template <typename T>
	NETClass<T>::~NETClass()
	{

	}

	template <typename T>
	NETClass<T>::NETClass(const NETClass& source)
		: NEClassBase(source)
	{

	}

	template <typename T>
	NETClass<T>::NETClass()
		: NEClassBase()
	{

	}

	template <typename T>
	NEObject& NETClass<T>::clone() const
	{
		return *(new This(*this));
	}

	template <typename T>
	NEObject& NETClass<T>::instantiate() const
	{
		return *(new Trait());
	}

	template <typename T>
	const NEClassBaseList& NETClass<T>::getSubClasses() const
	{
		return getSubClassesStatically();
	}

	template <typename T>
	const bool& NETClass<T>::isRegistered() const
	{
		return isRegisteredStatically();
	}

	template <typename T>
	const NEClassBaseList& NETClass<T>::getSuperClasses() const
	{
		return getSuperClassesStatically();
	}

	template <typename T>
	const NETString& NETClass<T>::getName() const
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

#define GENERATE_STATIC_METHOD(return_type, method_name)	\
	template <typename T>									\
	const return_type &NETClass<T>::method_name()		\
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