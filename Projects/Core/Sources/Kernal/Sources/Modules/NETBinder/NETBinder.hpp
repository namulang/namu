#pragma once

#include "NETBinder.inl"

namespace NE
{
	template <typename T>
	NETBinder<T>::~NETBinder()
	{
		unbind();
	}

	template <typename T>
	type_result NETBinder<T>::bind(const T& target)
	{
		// TODO:
		return RESULT_SUCCESS;
	}

	template <typename T>
	type_result NETBinder<T>::unbind()
	{
		// TODO:
		return RESULT_SUCCESS;
	}
}