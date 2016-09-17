#pragma once

#include "NETCIterator.inl"

namespace NE
{
	NE_DEFINE_INTERFACE_ONLY(NETCIterator<T>, template <typename T>)

	template <typename T>
	NETCIterator<T>::NETCIterator(const NEIteratorBase& origin)
		: Super(), _proxy(origin);
	{
	
	}

	template <typename T>
	NETCIterator<T>::NETCIterator(const This& rhs)
		: Super(rhs)
	{
		_assign(rhs);
	}

	template <typename T>
	NETCIterator<T>::~NETCIterator()
	{
		_release();
	}

	template <typename T>
	type_result NETCIterator<T>::next(type_count step_for_next)
	{
		if( ! _proxy.isBinded())
			return RESULT_TYPE_WARNING;

		return _proxy->next(step_for_next);
	}

	template <typename T>
	type_result NETCIterator<T>::back(type_count step_for_next)
	{
		if( ! _proxy.isBinded())
			return RESULT_TYPE_WARNING;

		return _proxy->back(step_for_next);
	}

	template <typename T>
	const T& NETCIterator<T>::get() const
	{
		T* nullpointer = NE_NULL;
		if(	! _proxy.isBinded()		||
			this == &_proxy.get()	)
			return *nullpointer;

		return *_proxy;
	}

	template <typename T>
	NEObject& NETCIterator<T>::clone() const
	{
		return *(new This(*this));
	}

	template <typename T>
	void NETCIterator<T>::release()
	{
		_proxy.release();	
	}

	template <typename T>
	NEBinaryFileSaver& NETCIterator<T>::serialize(NEBinaryFileSaver& saver) const
	{
		//	TODO: if we don't use binder, we can't save it.
		return saver << _proxy;
	}

	template <typename T>
	NEBinaryFileLoader& NETCIterator<T>::serialize(NEBinaryFileLoader& loader)
	{
		//	same as above.
		return loader >> _proxy;
	}

	template <typename T>
	type_result NETCIterator<T>::isValid() const
	{
		if( ! _proxy.isBinded()) return RESULT_TYPE_WARNING;

		return RESULT_SUCCESS;
	}

	template <typename T>
	NETCIterator<T>& NETCIterator<T>::operator=(const This& rhs)
	{
		if(this == &rhs) return *this;

		Super::operator=(rhs);

		return _assign(rhs);
	}

	template <typename T>
	type_bool NETCIterator<T>::operator==(const This& rhs) const
	{
		type_int evaluation = _proxy.isBinded() + rhs._proxy.isBinded();
		if(evaluation < 2)
			return evaluation == 0;

		return &_proxy.get() == &rhs._proxy.get();
	}

	template <typename T>
	type_bool NETCIterator<T>::operator!=(const This& rhs) const
	{
		return ! operator==(rhs);
	}

	template <typename T>
	NETCIterator<T>& NETCIterator<T>::operator++()
	{
		return static_cast<This&>(Super::operator++());
	}

	template <typename T>
	NETCIterator<T>& NETCIterator<T>::operator--()
	{
		return static_cast<This&>(Super::operator--());
	}

	template <typename T>
	NETCIterator<T> NETCIterator<T>::operator+(type_count step_for_next)
	{
		return static_cast<This&>(Super::operator+(step_for_next));
	}

	template <typename T>
	NETCIterator<T> NETCIterator<T>::operator-(type_count step_for_back)
	{
		return static_cast<This&>(Super::operator-(step_for_back));
	}

	template <typename T>
	const T& NETCIterator<T>::operator*() const
	{
		return get();
	}

	template <typename T>
	const T& NETCIterator<T>::operator->() const
	{
		return get();
	}

	template <typename T>
	NETCIterator<T>& NETCIterator<T>::_assign(const This& rhs)
	{
		release();

		_proxy = rhs._proxy;

		return *this;
	}

	NE_DEFINE_INTERFACE_ONLY(NETIterator<T>, template <typename T>)
	
	template <typename T>
	NEIterator<T>::NEIterator()
		: Super()
	{

	}

	template <typename T>
	NEIterator<T>::NEIterator(const NEIteratorBase& origin)
		: Super(origin)
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
		if( ! _proxy.isBinded()		||
			this == &_proxy.get()	)
			return *nullpointer;

		return *_proxy;
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