namespace NE
{
	template <typename T>
	NETInterface<T>::~NETInterface()
	{

	}

	template <typename T>
	NETInterface<T>::NETInterface(const NETInterface& source)
		: Super(source)
	{

	}

	template <typename T>
	NETInterface<T>::NETInterface()
		: Super()
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
}