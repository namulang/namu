#pragma once

#include "NETConstIterator.inl"

namespace NE
{
	NE_DEFINE_INTERFACE_ONLY(NETConstIterator<T>, template <typename T>)

	template <typename T>
	NETConstIterator<T>::NETConstIterator(const This* proxy)
		: _proxy(NE_NULL)
	{

	}

	template <typename T>
	NETConstIterator<T>::NETConstIterator(const This* proxy)
		: _proxy(&proxy.clone())
	{

	}

	template <typename T>
	NETConstIterator<T>::NETConstIterator(const This& rhs)
		: _proxy(NE_NULL)
	{
		_assign(proxy);
	}

	template <typename T>
	NETConstIterator<T>::~NETConstIterator()
	{
		_release();
	}

	template <typename T>
	type_result NETConstIterator<T>::next(type_count step_for_next)
	{
		if( ! _proxy)
			return RESULT_TYPE_WARNING;

		return _proxy->next(step_for_next);
	}

	template <typename T>
	type_result NETConstIterator<T>::back(type_count step_for_next)
	{
		if( ! _proxy)
			return RESULT_TYPE_WARNING;

		return _proxy->back(step_for_next);
	}

	template <typename T>
	const T& NETConstIterator<T>::get() const
	{
		T* nullpointer = NE_NULL;
		if( ! _proxy		||
			this == _proxy	)
			return *nullpointer;

		return _proxy->get();
	}

	template <typename T>
	NEObject& NETConstIterator<T>::clone() const
	{
		return *(new This(*this));
	}

	template <typename T>
	void NETConstIterator<T>::release()
	{
		_release();

		if(_proxy)
			_proxy->release();
	}

	template <typename T>
	NEBinaryFileSaver& NETConstIterator<T>::serialize(NEBinaryFileSaver& saver) const
	{
		//	TODO: if we don't use binder, we can't save it.
		return saver;
	}

	template <typename T>
	NEBinaryFileLoader& NETConstIterator<T>::serialize(NEBinaryFileLoader& loader)
	{
		//	same as above.
		return loader;
	}

	template <typename T>
	type_result NETConstIterator<T>::isValid() const
	{
		if( ! _proxy) return RESULT_TYPE_WARNING;

		return _proxy->release();
	}

	template <typename T>
	NETConstIterator<T>& NETConstIterator<T>::operator=(const This& rhs)
	{
		if(this == &rhs) return *this;

		Super::operator=(rhs);

		return _assign(rhs);
	}

	template <typename T>
	type_bool NETConstIterator<T>::operator==(const This& rhs) const
	{
		type_bool	has_proxy = _proxy != NE_NULL,
					has_rhs_proxy = rhs._proxy != NE_NULL;
		type_int	evaluation = has_proxy + has_rhs_proxy;
		if(evaluation < 2)
			return evaluation == 0;

		return _proxy->operator==(*rhs._proxy);
	}

	template <typename T>
	type_bool NETConstIterator<T>::operator!=(const This& rhs) const
	{
		return ! operator==(rhs);
	}

	template <typename T>
	NETConstIterator<T>& NETConstIterator<T>::operator++()
	{
		return static_cast<This&>(Super::operator++());
	}

	template <typename T>
	NETConstIterator<T>& NETConstIterator<T>::operator--()
	{
		return static_cast<This&>(Super::operator--());
	}

	template <typename T>
	NETConstIterator<T> NETConstIterator<T>::operator+(type_count step_for_next)
	{
		return static_cast<This&>(Super::operator+(step_for_next));
	}

	template <typename T>
	NETConstIterator<T> NETConstIterator<T>::operator-(type_count step_for_back)
	{
		return static_cast<This&>(Super::operator-(step_for_back));
	}

	template <typename T>
	const T& NETConstIterator<T>::operator*() const
	{
		return get();
	}

	template <typename T>
	const T& NETConstIterator<T>::operator->() const
	{
		return get();
	}

	template <typename T>
	void NETConstIterator<T>::_release()
	{
		if(_proxy)
		{
			_proxy->release();
			delete _proxy;
		}
		_proxy = NE_NULL;
	}

	template <typename T>
	NETConstIterator<T>& NETConstIterator<T>::_assign(const This& rhs)
	{
		release();

		if(rhs._proxy)
			_proxy = &static_cast<This&>(rhs._proxy->clone());

		return *this;
	}

	NE_DEFINE_INTERFACE_ONLY(NETIterator<T>, template <typename T>)
	
	template <typename T>
	NEIterator<T>::NEIterator()
		: Super()
	{

	}

	template <typename T>
	NEIterator<T>::NEIterator(const This* proxy)
		: Super(proxy)
	{

	}

	template <typename T>
	NEIterator<T>::NEIterator(const This& rhs)
		: Super(rhs)
	{

	}

	template <typename T>
	T& NETIterator<T>::get()
	{
		T* nullpointer = NE_NULL;
		if( ! _proxy		||
			this == _proxy	)
			return *nullpointer;

		return _proxy->get();
	}

	template <typename T>
	NEObject& NETIterator<T>::clone() const
	{
		return *(new This(*this));
	}

	template <typename T>
	NETIterator<T>& NETIterator<T>::operator++()
	{
		return static_cast<This&>(Super::operator++());
	}

	template <typename T>
	NETIterator<T>& NETIterator<T>::operator++()
	{
		return static_cast<This&>(Super::operator--());
	}

	template <typename T>
	NETIterator<T> NETIterator<T>::operator+(type_count step_for_next)
	{
		return static_cast<This&>(Super::operator+(step_for_next));
	}

	template <typename T>
	NETIterator<T> NETIterator<T>::operator-(type_count step_for_back)
	{
		return static_cast<This&>(Super::operator-(step_for_back));
	}

	template <typename T>
	const T& NETIterator<T>::operator*() const
	{
		return (const T&) get();
	}

	template <typename T>
	const T& NETIterator<T>::operator->() const
	{
		return (const T&) get();
	}
}