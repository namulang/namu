#pragma once

#include "Bind.hpp"

namespace wrd
{
	template <typename T>
	class TWeak : public Bind 
	{	WRD_CLASS_DECL(TWeak, Bind)
		friend class Block;
	public:
		TWeak();
		TWeak(T& it);
		TWeak(T* it);
		TWeak(This& it);
		TWeak(This* it);

	public:
        const T* operator->() const;
        const T* operator*() const;
        T* operator->();
        T* operator*();
		This& operator=(const This& rhs);

	public:	// Bind:
		Res& bind(T& new1);
		virtual Res& unbind();
		virtual const Class& getBindable() const;
		using Bindable::get;
		T& get();
		const T& get() const;
		//	Node:
		virtual wbool isConst() const;

	protected://Bind:
		virtual Res& _bind(const Instance& it);
	};
	template <typename T>
	class TWeak<const T> : public Bind 
	{	WRD_CLASS_DECL(TWeak, Bind)
		friend class Block;
	public:
		TWeak();
		TWeak(T& it);
		TWeak(T* it);
		TWeak(This& it);
		TWeak(This* it);
		TWeak(const T& it);
		TWeak(const T* it);
		TWeak(const This& it);
		TWeak(const This* it);

	public:
        const T* operator->() const;
        const T* operator*() const;
		This& operator=(This& rhs);
		This& operator=(const This& rhs);

	public:	// Bind:
		Res& bind(T& new1);
		Res& bind(const T& new1);
		virtual Res& unbind();
		virtual const Class& getBindable() const;
		using Bindable::get;
		const T& get() const;
		//	Node:
		virtual wbool isConst() const;

	protected://Bind:
		virtual Res& _bind(const Instance& it);
	};

	//	c++11 부터 지원되는 문법
	using Weak = TWeak<Node>;
	using CWeak = TWeak<const Node>;
}
