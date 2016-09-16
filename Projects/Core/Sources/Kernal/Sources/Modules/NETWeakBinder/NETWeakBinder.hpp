#pragma once

#include "NETWeakBinder.inl"

namespace NE
{
	template <typename T, type_bool>
	type_result NETWeakBinder<T>::bind(const T& target)
	{
		// TODO:
		return RESULT_SUCCESS;
	}

	template <typename T>
	T& NETWeakBinder<T>::operator->()
	{
		return get();
	}

	template <typename T>
	const T& NETWeakBinder<T>::operator->() const
	{
		return get();
	}

	template <typename T>
	T& NETWeakBinder<T>::operator*()
	{
		return get();
	}

	template <typename T>
	const T& NETWeakBinder<T>::operator*() const
	{
		return get();
	}

	template <typename T>
	T& NETWeakBinder<T>::get() 
	{
		NEUnit& binded = Super::get();
		if( ! binded.isSubClassOf(T::getClassStatically()))
		{
			T* nullpointer = NE_NULL;
			return *nullpointer;
		}

		return static_cast<T&>(binded);
	}

	template <typename T>
	const T& NETWeakBinder<T>::get() const
	{
		const NEUnit& binded = Super::get();
		if( ! binded.isSubClassOf(T::getClassStatically()))
		{
			T* nullpointer = NE_NULL;
			return *nullpointer;
		}

		return static_cast<const T&>(binded);
	}
}