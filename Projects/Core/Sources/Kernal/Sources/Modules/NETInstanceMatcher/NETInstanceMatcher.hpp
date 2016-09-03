#pragma once

#include "NETInstanceMatcher.inl"
#include "../NETClass/NETClass.hpp"

namespace NE
{
	NE_DEFINE_CLASS_ONLY(NETInstanceMatcher<T>, template <typename T>)

	template <typename T>
	NE::NETInstanceMatcher<T>::NETInstanceMatcher(const T& instance_target)
		: _target(instance_target)
	{

	}

	template <typename T>
	const T& NE::NETInstanceMatcher<T>::getTarget() const
	{
		return _target;
	}

	template <typename T>
	type_bool NE::NETInstanceMatcher<T>::operator()(const T& source) const
	{
		return source == target;
	}
}