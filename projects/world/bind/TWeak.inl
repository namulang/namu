#pragma once

#include "../base/Trace.hpp"
#include "TBindable.inl"
#include "../base/TGettable.inl"

namespace wrd
{
	class Block;
	class Res;
	class Node;

	//	Hierarchy:
	//		Instance <- TGettable<Instance> <- TBindable <- Trace <- TGettable<T> <-
	//		TWeak<T>
	template <typename T>
	class TWeak : public TGettable<T, Trace>
	{	WRD_CLASS_DECL_2(TWeak, TGettable<T WRD_COMMA() Trace>)
	public:
		TWeak();
		TWeak(const T& it);
		TWeak(const T* it);
		template <typename V> TWeak(const TBindable<V>& rhs) : Super() { bind(rhs.get()); }

	public:
		This& operator=(const This& rhs);
		This& operator=(const T& newone);
		This& operator=(const T* newone);
		wbool operator==(const This& rhs) const;
		wbool operator!=(const This& rhs) const;

	public:	// TBindable:
		using Super::bind;
		virtual Res& bind(const Instance& new1);
		virtual Res& unbind();
		virtual wbool isBind() const;

	public:	// Thing:
		//TODO: replace this. put API on Thing. virtual ResSet isValid() const;
		virtual Res& release();

	protected:
		virtual Instance& _get(); // TODO: impl this.
	};

	//	c++11 부터 지원되는 문법
	using Weak = TStrong<Node>;
	using CWeak = TStrong<const Node>;
}
