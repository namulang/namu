#pragma once

#pragma message "4-2-1-1"
#include "../bases/Trace.hpp"
#pragma message "4-2-1-2"
#include "../bases/TGettable.inl"
#pragma message "4-2-1-3"

namespace wrd
{
	class Block;
	class Result;
	class Node;

	template <typename T>
	class TWeak : public TGettable<T, Trace>
	{	WRD_INHERIT_2(TWeak, TGettable<T WRD_COMMA() Trace>)
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
		virtual const Class& getClass() const;
		virtual Result& release();

	protected:
		virtual Instance& _get(); // TODO: impl this.
	};

	//	c++11 부터 지원되는 문법
	using Weak = TStrong<Node>;
	using CWeak = TStrong<const Node>;
}
