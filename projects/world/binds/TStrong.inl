#pragma once

#include "./TWeak.inl"

namespace wrd
{
	class Node;

	template <typename T>
	class TStrong : public TWeak<T>
	{
	public:
		TStrong();
		TStrong(T& it);
		TStrong(T* it);
		TStrong(Bindable& it);

	public:
		virtual Result& bind(T& it);
		virtual Result& unbind();
	};
	//	c++11 부터 지원되는 문법
	using Strong = TStrong<Node>;
	using CStrong = TStrong<const Node>;
}
