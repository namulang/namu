namespace NE
{
	template <typename T>
	void NETHeader<T>::_release()
	{
		_version.release();
		_comment.release();
		_compatibles.release();
	}

	template <typename T>
	NETHeader<T>& NETHeader<T>::_assign(const This& rhs)
	{
		_version = rhs._version;
		_comment = rhs._comment;
		_compatibles = rhs._compatibles;

		return *this;
	}

	template <typename T>
	NEBinaryFileLoader& NETHeader<T>::serialize(NEBinaryFileLoader& loader)
	{
		Super::serialize(loader);

		return loader >> _version >> _comment >> _compatibles;
	}

	template <typename T>
	NEBinaryFileSaver& NETHeader<T>::serialize(NEBinaryFileSaver& saver) const
	{
		Super::serialize(saver);

		return saver << _version << _comment << _comment;
	}

	template <typename T>
	type_result NETHeader<T>::isValid() const
	{
		type_result result = Super::isValid();
		if(NEResult::hasError(result)) return result;

		return RESULT_SUCCESS;
	}

	template <typename T>
	void NETHeader<T>::release()
	{
		Super::release();

		_release();
	}

	template <typename T>
	type_result NETHeader<T>::setCompatibleSet(const NEIntSet& new_compatibles)
	{
		_compatibles = new_compatibles;

		return RESULT_SUCCESS;
	}

	template <typename T>
	const NEIntSet& NETHeader<T>::getCompatibleSet() const
	{
		return _compatibles;
	}

	template <typename T>
	type_result NETHeader<T>::setComment(const NETString& new_comment)
	{
		_comment = new_comment;

		return RESULT_SUCCESS;
	}

	template <typename T>
	const NETString& NETHeader<T>::getComment() const
	{
		return _comment;
	}

	template <typename T>
	type_result NETHeader<T>::setVersion(const NETString& new_version)
	{
		_version = new_version;

		return RESULT_SUCCESS;
	}

	template <typename T>
	const NETString& NETHeader<T>::getVersion() const
	{
		return _version;
	}

	template <typename T>
	type_bool NETHeader<T>::operator!=(const This& rhs)
	{
		return ! operator==(rhs);
	}

	template <typename T>
	type_bool NETHeader<T>::operator==(const This& rhs)
	{
		return	Super::operator==(rhs)				&&
			_comment == rhs._comment			&&
			_version == rhs._version			&&
			_compatibles == rhs._compatibles	;
	}

	template <typename T>
	NETHeader<T>& NETHeader<T>::operator=(const This& rhs)
	{
		if(this == &rhs) return *this;

		Super::operator=(rhs);

		return _assign(rhs);
	}

	template <typename T>
	NETHeader<T>::~NETHeader()
	{

	}

	template <typename T>
	NETHeader<T>::NETHeader(const This& rhs)
		: Super(rhs)
	{
		_assign(rhs);
	}

	template <typename T>
	NETHeader<T>::NETHeader()
		: Super()
	{

	}
}