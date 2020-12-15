#pragma once

#include "Bind.hpp"

namespace wrd { namespace memlite {

	template <typename T>
	class TWeak : public Bind
	{	WRD_DEF_THIS(TWeak)
		friend class BindTag;

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
		wbool bind(T& new1);
		virtual const Type& getBindable() const;
		T& get();
		const T& get() const;
		//	Node:
		virtual wbool isConst() const;
	};
	template <typename T>
	class TWeak<const T> : public Bind 
	{	WRD_DECL_THIS(TWeak, Bind)
		friend class BindTag;
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
		wbool bind(T& new1);
		wbool bind(const T& new1);
		virtual const Type& getBindable() const;
		const T& get() const;
		//	Node:
		virtual wbool isConst() const;
	};
}}
