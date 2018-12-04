#pragma once

#include "../bases/Instance.hpp"

namespace wrd
{
	class InstanceBlock;
	class Result;
	class Node;

	template <typename T>
	class TWeak : public Thing
	{
	public:
		// TODO: static_assert(T is not sub of Instance)
		// TODO: remove below line
		typedef TWeak<T> This;
		TWeak();
		TWeak(T& it);
		TWeak(T* it);
		TWeak(const This& rhs);

	public:
		This& operator=(const This& rhs);
		This& operator=(T& newone);
		This& operator=(T* newone);
		wbool operator==(const This& rhs) const;
		wbool operator!=(const This& rhs) const;
		operator wbool() const;
		const T* operator->() const; 
		T* operator->();
		const T* operator*() const;
		T* operator*();

	public:
		virtual Result& bind(T& newone);
		Result& bind(This& rhs);
		Result& bind(T* newone);
		virtual Result& unbind();
		const T& get() const;
		T& get();
		wbool isBinded() const;
		virtual Result& release();
		//TODO: replace this. put API on Thing. virtual ResultSet isValid() const;
		virtual const Class& getClass() const;

	private:
		const InstanceBlock& _getInstanceBlock() const;
		InstanceBlock& _getInstanceBlock();

	private:
		Instance::ID _id;
		wcnt _serial;
	};
	//	c++11 부터 지원되는 문법
	using Weak = TStrong<Node>;
	using CWeak = TStrong<const Node>;
}
