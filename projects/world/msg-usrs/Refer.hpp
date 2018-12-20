#pragma once

#include "../bases/Node.hpp"
#include "../bases/TGettable.hpp"
#include "../binds/Bindable.hpp"

namespace wrd
{
    class Refer : public TGettable<Instance, Node>, public Bindable
	{	WRD_CLASS_2(Refer, TGettable<Instance WRD_COMMA() Node>)
	public:
		//TODO: uncomment this. Refer(const Class& cls = Node::getStaticClass(), wbool want_const = false);
		Refer(Node& it);
		Refer(const Node& it);
		Refer(const Refer& it);
		Refer(Refer& it);

	public:
		wbool operator==(const Refer& rhs) const;
		wbool operator!=(const Refer& rhs) const;
		Refer& operator=(const Refer& it);
		Refer& operator=(Refer& it);
		Refer& operator=(Node& it);
		Refer& operator=(const Node& it);

	public:	//	Node:
		virtual Refer use(Msg& msg) const; 
		virtual Refer use(Msg& msg); 
		virtual const Origin& getOrigin() const; 
		virtual wbool isConst() const; 
		virtual const Container& getNodes() const;

	public:	//	Bindable:
		using TBindable<Node>::bind;
		virtual Result& bind(Instance& it);
		Result& bind(Refer& it);
		Result& bind(const Refer& it);
		Result& bind(const Instance& it);
		virtual wbool isBind() const;
		Result& unbind();

	public:	//	Thing:
		virtual Refer to(const Class& cls);
		virtual Result& assign(const Thing& it);
		virtual const Class& getClass() const;

	protected:
		virtual Instance& _get();
		//	TODO: const cast.
		//		Refer는 알다시피 World의 const를 구현하는 핵심 클래스다.
		//		Node& n = Refer(const T&..);
		//		n.to<T>(); // REJECT. return Refer(Null)
		//		T& cast = n.down<T>(); // REJECT. cast.isNull() == true.
		//		const T& cast = n.down<const T>(); // OK.
		//		Refer& cast1 = n.to<const T>(); // OK. cast1->isNull() != true
		//	위의 코드가 가능하도록 해야 한다.
		virtual Node& _cast(const Class& cls);
		virtual const Node& _cast(const Class& cls) const;

	private:
		wbool _is_const;
		Strong _bean;
		const Class& _cls;
	};
}
