namespace NE
{
	template <typename T>
	NEArgumentTemplate<T>::NEArgumentTemplate() 
		: SuperClass(T().getType())
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
	typename T::Trait& NE::NEArgumentTemplate<T>::getValue() 
	{
		if(isBinded())
		{
			NEKey& binded = getBinded();
			if(binded.getType() == getTypeToBeBinded())
				return getBindedKey().getValue();

			_for_casting = binded;
			_setNeedingUpdate(true);
			return _for_casting.getValue();
		}

		T::Trait* nullpointer = 0x00;
		return *nullpointer;
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
			_setNeedingUpdate(true);
			return getDefault();
		}

		const T::Trait* nullpointer = 0x00;
		return *nullpointer;
	}

	template <typename T>
	type_result NEArgumentTemplate<T>::update()
	{
		type_result result = RESULT_SUCCESS | RESULT_ABORT_ACTION;
		if( ! isNeedingUpdate()) return result;
		if( ! isBinded()) return result;

		NEKey& binded = getBinded();		
		binded = _for_casting;

		return RESULT_SUCCESS;
	}
}