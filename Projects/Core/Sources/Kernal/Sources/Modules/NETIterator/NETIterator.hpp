#pragma once

#include "NETCIterator.inl"

namespace NE
{
	NE_DEFINE_INTERFACE_ONLY(NETCIterator<T>, template <typename T>)

	template <typename T>
	NETCIterator<T>& NETCIterator<T>::operator++()
	{
		next();

		return *this;
	}

	template <typename T>
	NETCIterator<T>& NETCIterator<T>::operator--()
	{
		back();

		return *this;
	}

	template <typename T>
	NETCIterator<T> NETCIterator<T>::operator+(type_count step_for_next)
	{
		This copied(*this);
		copied.next(step_for_next);

		return copied;
	}

	template <typename T>
	NETCIterator<T> NETCIterator<T>::operator-(type_count step_for_back)
	{
		This copied(*this);
		copied.back(step_for_back);

		return copied;
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
	type_bool NETCIterator<T>::operator<(const This& rhs) const
	{
		NETBinder<This> e(clone());
		for(; ! e->isEnd() ;*e--)
			if(*e == rhs)
				return true;

		return false;
	}

	template <typename T>
	type_bool NETCIterator<T>::operator>(const This& rhs) const
	{
		NETBinder<This> e(clone());
		for(; ! e->isEnd() ;*++e)
			if(*e == rhs)
				return true;

		return false;
	}

	NE_DEFINE_INTERFACE_ONLY(NETIterator<T>, template <typename T>)
	
	template <typename T>
	NETIterator<T>& NETIterator<T>::operator++()
	{
		next();

		return *this;
	}

	template <typename T>
	NETIterator<T>& NETIterator<T>::operator++()
	{
		back();

		return *this;
	}

	template <typename T>
	NETIterator<T> NETIterator<T>::operator+(type_count step_for_next)
	{
		This copied(*this);
		copied.next(step_for_next);

		return copied;
	}

	template <typename T>
	NETIterator<T> NETIterator<T>::operator-(type_count step_for_back)
	{
		This copied(*this);
		copied.back(step_for_back);

		return copied;
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