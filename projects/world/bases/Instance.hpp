#pragma once

#include "Thing.hpp"

namespace wrd
{
	class InstanceBlock;
	class Node;
	template <typename T> class TWeak;
	template <typename T> class TStrong;

	class Instance : public Thing
	{
	public:
		//	Instance는 World에서 인스턴스 관리를 대신해준다. 여기서부터 bind가 가능하다.
		union ID
		{
			widx type;
			//	클래스의 종류
			widx index;
			//	해당 클래스 인스턴스 벡터의 몇번째인가.type과 index를 조합하면 어디서든 객체에 접근할 수 있다.
			wint64 number;
		} _id;

	public:
		Instance();
		//	why was virtual copyconstructor defined with private accessor?:
		//		WorldFrx basically is based on class Node.
		//		So, if all classes returns TStrong<Instance> as a returntype of clone()
		//		user may needs to cast it to Node. inconvenient.
		//		however, if we declared this as a private member-function and 
		//		define clone() non-virtual function as public, we can return Node
		//		as a return-type of clone if it's subclass of Node.
		//
		//	in summary:
		//		clone()  : a wrapper for providing easy-to-use return type.
		//		_clone() : it's a really what cloning happens. subclasses will
		//		override it.
		TStrong<Instance> clone() const;
		ID getID() const;
		wcnt getSerial() const;
		const InstanceBlock& getBlock() const;
		wbool isHeap() const;
		TStrong<Node> toStrong();
		TStrong<const Node> toStrong() const;
		TWeak<Node> toWeak();
		TWeak<const Node> toWeak() const;

	private:
		virtual TStrong<Instance> _clone() const;
	};
}
