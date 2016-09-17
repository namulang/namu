#pragma once

#include "NETWeakBinder.inl"

namespace NE
{
#define _TEMPLATE	template <typename T, type_bool>
#define _NAME		NETWeakBinder<T, type_bool>

	_TEMPLATE
	_NAME::NETWeakBinder()
		: Super()
	{

	}

	_TEMPLATE
	_NAME::NETWeakBinder(const T& target)
		: Super()
	{
		This::bind(target);
	}

	_TEMPLATE
	_NAME::NETWeakBinder(const This& rhs)
		: Super(rhs)
	{
		This::bind(*rhs);
	}

	_TEMPLATE
	_NAME::~NETWeakBinder()
	{
		unbind();
	}

	_TEMPLATE
	type_result _NAME::bind(const T& target)
	{
		if( ! &target) return RESULT_TYPE_WARNING;
		if(isBinded())
		{
			if( &get() == &target)
				return RESULT_SUCCESS | RESULT_ABORT_ACTION;
			unbind();
		}


		// TODO:
		return RESULT_SUCCESS;
	}

	_TEMPLATE
	T& _NAME::operator->()
	{
		return get();
	}

	_TEMPLATE
	const T& _NAME::operator->() const
	{
		return get();
	}

	_TEMPLATE
	T& _NAME::operator*()
	{
		return get();
	}

	_TEMPLATE
	const T& _NAME::operator*() const
	{
		return get();
	}

	_TEMPLATE
	T& _NAME::get() 
	{
		NEUnit& binded = Super::get();
		if( ! binded.isSubClassOf(T::getClassStatically()))
		{
			T* nullpointer = NE_NULL;
			return *nullpointer;
		}

		return static_cast<T&>(binded);
	}

	_TEMPLATE
	const T& _NAME::get() const
	{
		const NEUnit& binded = Super::get();
		if( ! binded.isSubClassOf(T::getClassStatically()))
		{
			T* nullpointer = NE_NULL;
			return *nullpointer;
		}

		return static_cast<const T&>(binded);
	}

#undef _NAME
#undef _TEMPLATE
}