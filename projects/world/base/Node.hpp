#pragma once

#include "State.hpp"
#include "../compiler/Origin.hpp"

namespace wrd
{
	//	World에서 const 구현:
	//		개요:
	//			Managed에서 생성된 객체는 occupiable이라도 const로 정의되어있으면
	//			Strong(isConst() = true)에 감싸여져서 scope나 owner Node에 등어간다.
	//			Strong는 c++에서는 nonconst 라도, isConst() = true라면 get(); 에서는
	//			nullref가 나오게 된다. get() const; 에서는 정상적으로 Reference가
	//			나온다. 
	//
	//		CStrong, Strong 2개의 클래스로 나누지 않는 이유는:
	//			1. CStrong, Strong로 나누는 것은 사실 중요하지 않다. 왜냐하면 World는
	//			Node를 기준으로 "구체 클래스가 뭔지 몰라도 되게 한다" 라는 설계
	//			철학을 기반으로 했기 때문이다. Node 만 안 시점에 native 개발자는
	//			이것이 CStrong인지 Strong인지 관련없이 동일하게 작업을 수행할 수 
	//			있어야 하고, 이는 공통적인 인터페이스(to())가 있어야 한다는 걸
	//			시사한다.
	//
	//			2. 개발자는 Node와 Strong를 구분하고 싶은 경우가 있다. 이때 CStrong가
	//			있다면 RTTI가 최소 2번은 들어가야 한다.
	//				Node& origin = ...;
	//				Strong& is_refer = origin.to<CStrong>();
	//				if(is_refer.isNull()) {
	//					CStrong& is_crefer = origin.to<CStrong>();
	//					...
	//				} else {
	//					...
	//				}
	//			그리고 물론 이 방법은 마음에 들지 않을 것이다.
	//
	//			Strong가 isConst()가 false라고 하더라도 C++적으로 const라면 isConst
	//			()와 동일하게 동작한다. 이는 C++에서 ptr에 대한 const라고 보면
	//			되며, isConst()는 ptr가 가리키는 인스턴스에 대한 const라고 보면
	//			이해가 빠를 것이다.
	//			World는 ptr가 밖으로 들어내지 않기 때문에 ptr에 대한 const는
	//			존재하지 않는다. 그걸 c++의 const가 대신하는 것이라고 여기면 된다.
	//
	//		Node의 각 구체클래스별 const 구현:
	//			임의의 구체클래스A가 isConst() == true이거나 C++적으로 const일 경우,
	//			동일하게 const 객체로 간주한다.
	//			단, 구체클래스 A가 Method의 경우일때는 예외이다. Method는 c++의
	//			const 의미가 없으며 모두 nonconst이다.
	//			이는 Method의 const 여부는 런타임에 binding된 식별자에 의해서
	//			결정되는 것이 아니라, 정적으로 컴파일시
	//			결정되기 때문이다. 이는 method.isConst()에 의해서만 판가름된다.
	//
	//			구체클래스	|	const객체일때			|	nonconst객체일때		
	//			------------------------------------------------------------------------
	//			Strong		|	object.use() const		|	object.use()
	//			------------------------------------------------------------------------
	//			Object		|	sub_method.use() const	|	sub_method.use()
	//			------------------------------------------------------------------------
	//			Method		|	항상 execute()			|	use() const로 온 경우는 X
	//			------------------------------------------------------------------------
	//				*) Method는 isConst()의 값에 의해서만 const객체냐 아니냐가 결정된다.
	//				*) Method가 const객체라는 뜻은, const 메소드라는 것이다.
	class Str;
	class Container;
	class Msg;
	class Origin;

	class Node : public State 
	{	WRD_CLASS_DECL(Node, State)
	public:
		Node& operator[](widx n);
		const Node& operator[](widx n) const;
		wbool operator==(const This& rhs);
		wbool operator!=(const This& rhs);

	public:
		//	Node:
		//TODO?: ???? 왜 name을 내보내지?? 오타인가? const Str& getName() const;
		//Str& getName();
		virtual wbool isOccupy() const;
		virtual const Container& getNodes() const = 0;
		//	getNodes:
		//		모든 Container의 index는 World와 Native모두 1부터 시작한다.
		//		invisible하다.
		Node& getNode(widx n);
		const Node& getNode(widx n) const;
		Node& getNode(const Str& name);
		const Node& getNode(const Str& name) const;
		virtual Strong use(Msg& msg);
		virtual CStrong use(Msg& msg) const;
		virtual WRD_LAZY_METHOD(Origin&, getOrigin, const, Origin&, nulr<Origin>());
		virtual wbool canUse(const Msg& msg) const;
		virtual wbool isStatic() const;
		virtual wbool isConst() const;
		virtual Strong implicit(const Class& cls);
		CStrong implicit(const Class& cls) const;
		//	Instance:
		virtual Strong toStrong();
		virtual Weak toWeak();

	protected:
		//	get(); 는 공개하지 않는다:
		//		사용자는 Container채로 받게 되면 밖에서 remove, insert를 할 수 있게 된다.
		Container& _getNodes();
		Container& _get();
		Node& _get(wbool want_const, std::function<wbool(Node&)> tester);
	};
}
