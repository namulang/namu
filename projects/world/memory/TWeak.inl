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
		TWeak(const This& rhs);

	public:
        const T* operator->() const;
        const T& operator*() const;
        T* operator->();
        T& operator*();
		This& operator=(const This& rhs);

	public:	// Bind:
		Res& bind(T& new1);
		virtual const Class& getBindable() const;
		using Bindable::get;
		T& get();
		const T& get() const;
		//	Node:
		virtual wbool isConst() const;
	};
	template <typename T>
	class TWeak<const T> : public Bind 
	{	WRD_CLASS_DECL(TWeak, Bind)
		friend class Block;
	public:
		TWeak();
		TWeak(T& it);
		TWeak(T* it);
		TWeak(const T& it);
		TWeak(const T* it);
		TWeak(const This& rhs);
		TWeak(const TWeak<T>& rhs);

	public:
        const T* operator->() const;
        const T& operator*() const;
		This& operator=(const This& rhs);
		This& operator=(const TWeak<T>& rhs);

	public:	// Bind:
		Res& bind(T& new1);
		Res& bind(const T& new1);
		virtual const Class& getBindable() const;
		using Bindable::get;
		const T& get() const;
		//	Node:
		virtual wbool isConst() const;
	};

	typedef TWeak<Node> Weak;
	typedef TWeak<const Node> CWeak;
}
