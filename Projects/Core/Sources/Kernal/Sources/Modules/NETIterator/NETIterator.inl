#pragma once

#include "../NEIteratorBase/NEIteratorBase.hpp"

namespace NE
{
	//	What you have to know when you make subclass for NETIterator<T>:
	//		Don't define methods return its own class as return-type.
	//		So, don't do like below,
	//
	//			class MyIterator : public NETIterator<T> {
	//				MyIterator& operator++();
	//			}
	//
	//		But use this instead of above one if you have to.
	//
	//			NETIterator<T>& operator++();
	template <typename T>
	class NETCIterator : public NEIteratorBase 
	{
		NE_DECLARE_INTERFACE_ONLY(NETCIterator, NEIteratorBase)

	public:
		virtual type_result next(type_count step_for_next) = 0;
		virtual type_result back(type_count step_for_back) = 0;
		virtual const T& get() const = 0;

	public:
		//	Method hiding:		
		This& operator++();
		This& operator--();
		This operator+(type_count step_for_next);
		This operator-(type_count step_for_back);
		const T& operator*() const;
		const T& operator->() const;
	};

	template <typename T>
	class NETIterator : public NETCIterator 
	{
		NE_DECLARE_INTERFACE_ONLY(NETIterator, NEIteratorBase)

	public:
		virtual T& get() = 0;

	public:
		//	Method hiding:
		This& operator++();
		This& operator--();
		This operator+(type_count step_for_next);
		This operator-(type_count step_for_back);
		T& operator*();
		T& operator->();
	};
}