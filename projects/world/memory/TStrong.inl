#pragma once

#include "./TWeak.inl"

namespace wrd
{
	template <typename T>
	class TStrong : public TWeak<T>
	{	WRD_CLASS_DECL(TStrong, TWeak<T>)
	public:
		TStrong();
		TStrong(T& it);
		TStrong(T* it);
		TStrong(const This& rhs);

	public:
		This& operator=(const This& rhs);

	public:
		virtual Res& unbind();

	protected:
		//Bind:
		virtual Res& _bind(const Instance& it);
	};
	template <typename T>
	class TStrong<const T> : public TWeak<const T>
	{	WRD_CLASS_DECL(TStrong, TWeak<const T>)
	public:
		TStrong();
		TStrong(T& it);
		TStrong(T* it);
		TStrong(const T& it);
		TStrong(const T* it);
		TStrong(const This& rhs);
		TStrong(const TStrong<T>& rhs);

	public:
		This& operator=(const This& rhs);
		This& operator=(const TStrong<T>& rhs);

	public:
		virtual Res& unbind();

	protected:
		//Bind:
		virtual Res& _bind(const Instance& it);
	};

	typedef TStrong<Node> Strong;
	typedef TStrong<const Node> CStrong;
}
