#pragma once

#include "../bases/Trace.hpp"
#include "Bindable.hpp"
#include "../bases/TGettable.inl"

namespace wrd
{
	class Block;
	class Result;
	class Node;

	template <typename T>
	class TWeak : public TGettable<T, Trace>, public Bindable
	{	WRD_CLASS_DECLARE_2(TWeak, TGettable<T WRD_COMMA() Trace>)
	public:
		TWeak();
		TWeak(T& it);
		TWeak(T* it);
		TWeak(Bindable& rhs);

	public:
		This& operator=(const This& rhs);
		This& operator=(T& newone);
		This& operator=(T* newone);
		wbool operator==(const This& rhs) const;
		wbool operator!=(const This& rhs) const;

	public:	// TBindable:
		virtual Result& bind(Instance& new1);
		Result& bind(Bindable& rhs);
		virtual Result& unbind();
		virtual wbool isBind() const;

	public:	// Thing:
		//TODO: replace this. put API on Thing. virtual ResultSet isValid() const;
		virtual Result& release();

	protected:
		virtual Instance& _get(); // TODO: impl this.
	};

	//	c++11 부터 지원되는 문법
	using Weak = TStrong<Node>;
	using CWeak = TStrong<const Node>;
}
