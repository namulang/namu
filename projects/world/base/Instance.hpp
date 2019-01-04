#pragma once

#include "Thing.hpp"
#include "Id.hpp"

namespace wrd
{
	class Block;
	class Node;
	template <typename T> class TStrong;
	typedef TStrong<Node> Strong;
	typedef TStrong<const Node> CStrong;
    template <typename T> class TWeak;
	typedef TWeak<Node> Weak;
	typedef TWeak<const Node> CWeak;

	class Instance : public Thing
	{	WRD_CLASS_DECL(Instance, Thing)
		//	Instance는 World에서 인스턴스 관리를 대신해준다. 여기서부터 bind가 가능하다.

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

	public:
		wbool operator==(const This& rhs);
		wbool operator!=(const This& rhs);

	public://Instance:
		Id getId() const;
		wcnt getSerial() const;
		virtual wbool isHeap() const;
		Strong toStrong();
		CStrong toStrong() const;
		Weak toWeak();
		CWeak toWeak() const;
		const Block& getBlock() const;
		//	Thing:
		virtual Res& release();

	protected:
		static Block& _getBlock(Id id);
		Res& _setId(Id new1);

	private:
		Id _id;
	};
}
