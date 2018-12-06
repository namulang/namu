#pragma once

#include "TBindable.inl"

namespace wrd
{
	class InstBlk;
	class Result;
	class Node;

	template <typename T>
	class TWeak : public TBindable<T>
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

	public:	// TBindable:
		virtual Result& bind(Instance& new1);
		Result& bind(This& rhs);
		virtual Result& unbind();
		virtual wbool doesBind() const;

	public:	// Thing:
		virtual Result& release();
		//TODO: replace this. put API on Thing. virtual ResultSet isValid() const;
		virtual const Class& getClass() const;

	protected:
		virtual Instance& _get(); // TODO: impl this.

	private:
		const InstBlk& _getInstBlk() const;
		InstBlk& _getInstBlk();

	private:
		Instance::ID _id;
		wcnt _serial;
	};
	//	c++11 부터 지원되는 문법
	using Weak = TStrong<Node>;
	using CWeak = TStrong<const Node>;
}
