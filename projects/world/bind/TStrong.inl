#pragma once

#include "./TWeak.inl"

namespace wrd
{
	class Node;

	template <typename T>
	class TStrong : public TWeak<T>
	{	WRD_CLASS_DECL(TStrong, TWeak<T>)
	public:
		TStrong();
		TStrong(const T& it);
		TStrong(const T* it);
		template <typename V> TStrong(const TBindable<V>& rhs) : Super() { bind(rhs); }
		// TODO: 이런 생성자 지원을 어떻게 할까? TStrong(TBindable& it);
		// TWeak에는 넣을 수 없다. TStrong이 있으니. 그렇다고 빼기에는 좀 불편할 것 같고.
		// Refer는 어떻게 하나? 너무 추상클래스에 넣으면 동작이 불가능하고 (virtual이므로)
		// 구체에 넣을려고 하면 이번 TWeak 처럼 된다.
	public:
		using Super::operator=;
		template <typename V> This& operator=(const TBindable<V>& rhs) {
			this->bind(rhs);
			return *this;
		}

	public:
		using Super::bind;
		virtual Res& bind(const T& it);
		virtual Res& unbind();
	};
	//	c++11 부터 지원되는 문법
	using Strong = TStrong<Node>;
	using CStrong = TStrong<const Node>;
}
