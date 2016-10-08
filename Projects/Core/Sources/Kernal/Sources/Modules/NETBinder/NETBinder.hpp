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
		//	Remember. The sequence is the point:
		//		Consider bind another target means "some object destroyed because 
		//		of loosing".
		//		Bind First, reduce refcount later. if you don't, there are some 
		//		exceptions that instances were terminated cascade.
		//
		//		For example, there is a List.		
		//
		//			->	[A]	->	[B]	->	[C]
		//
		//		[A] means node of List, the arrow is binding.
		//		In this case, we're trying to change the binder of A to C, not B.
		//		
		//			->	[A]	->	[C]
		//						 ^
		//					[B]	-|		
		//
		//		[B] will be destroyed. there is no binder who bind it.
		//		Well, approximately this picture looks right. But how about [A]'s
		//		binder detach binding to B first rather than binding to C?
		//		
		//			->	[A]		[C]							->	[A]		[C] 
		//						 ^		--after a while-->				 ^
		//					[B]	-|										 |- removing
		//
		//		As you can see above, B was removed simultaniously.
		//		and because of removal of B, C has no other binder, will be destroyed 
		//		too. After that, A tries to bind to C, but there is no C any more.

	}

	template <typename T>
	type_result NETBinder<T>::_unbind()
	{
		if( ! isBinded()) return RESULT_TYPE_WARNING | RESULT_ABORT_ACTION;
		// TODO:
	}
}