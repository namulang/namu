#pragma once

#include "NETBinder.inl"

namespace NE
{
	template <typename T>
	NETBinder<T>::NETBinder()
		: Super()
	{

	}

	template <typename T>
	NETBinder<T>::NETBinder(const T& target)
		: Super(target)
	{
		_bind(target);
	}

	template <typename T>
	NETBinder<T>::NETBinder(const Super& rhs)
		: Super(rhs)
	{
		_bind(rhs.get());
	}

	template <typename T>
	NETBinder<T>::~NETBinder()
	{
		_unbind();
	}

	template <typename T>
	type_result NETBinder<T>::bind(const T& target)
	{
		Super::bind(target);

		return _bind(target);
	}

	template <typename T>
	type_result NETBinder<T>::unbind()
	{
		Super::unbind();

		return _unbind();
	}

	template <typename T>
	type_result NETBinder<T>::_bind(const T& target)
	{
		if( ! &target) return RESULT_TYPE_WARNING;

		// TODO:
	}

	template <typename T>
	type_result NETBinder<T>::_unbind()
	{
		if( ! isBinded()) return RESULT_TYPE_WARNING | RESULT_ABORT_ACTION;
		// TODO:
	}
}