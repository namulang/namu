		//	Usage:
		//		to:
		A& a = ...;
		Refer ra = a.to(TClass<AChild>());
		ra.isConst(); // false
		ra = a.to(TClass<const AChild>()); // TClass<const T> is compile err
		ra = a.to(TClass<Integer>());
		Integer casted = *ra.to<Integer>(); // T of to<T> should be a sort of Node.
		//	At this moment, the returned value from ra.to<>() copied to casted variable,
		//	and was deleted automatically.
		TRefer<const AChild> cra = ra.to<const AChild>();
		//	cra자체는 const가 아니다. World는 const Reference라는 게 없기 때문이다. ref가 가리키는게 const냐 아니냐만 존재한다.

		cra->nonconstMethod(); // compile err. TRefer<const>는 operator->() const만 있다.
		const TRefer<AChild> cra2 = cra;
		cra2->nonconstMethod(); // compile err.
		const A& ca = a;
		Refer cra3 = ca.to(TClass<AChild>());
		cra3.isConst(); // true
		cra3.call(...); // 본래 이렇게 하는게 정상이다.

		//	Refer.isConst()의 의미는 const T* 이다.
		//	const Refer& ref 의 의미도 const T* 이나, 이것은 엄밀히 말하면 Managed 인스턴스를 한번더 const 로 래핑한것과 같다. 왜냐하면 본래 모든 Managed객체는 C++에서는 nonconst로 접근가능하기 때문이다. 따라서 이러한 용법은 native에서 const임을 한번더 못박은거라고 보면 된다.


class Instance : Thing {
	//	Instance는 World에서 인스턴스 관리를 대신해준다. 여기서부터 bind가 가능하다.
	union ID {
		windex type;
		//	클래스의 종류
		windex index;
		//	해당 클래스 인스턴스 벡터의 몇번째인가.type과 index를 조합하면 어디서든 객체에 접근할 수 있다.
		wint64 number;
	} _id;

	Instance() {
		//	TODO: we need to optimize this. this ganna hotspot.
		Nexus::get().getInstancer().stamp(*this);
	}

	//	why was virtual copyconstructor defined with private accessor?:
	//		WorldFrx basically is based on class Node.
	//		So, if all classes returns TStrong<Instance> as a returntype of clone()
	//		user may needs to cast it to Node. inconvenient.
	//		however, if we declared this as a private member-function and 
	//		define clone() non-virtual function as public, we can return Node
	//		as a return-type of clone if it's subclass of Node.
	virtual TStrong<Instance> _clone() const {
		return TStrong<Instance>(new This(*this));
	}
	TStrong<Instance> clone() const {
		return _clone();
	}
	ID getID() const { return _id; }
	wcount getSerial() const { 
		Nexus::get().getInstancer()[_id].getSerial();
	}
	const InstanceBlock& getBlock() const {
		WRD_IS_THIS(InstanceBlock)
		return Nexus::get().getInstancer()[_id];
	}
	wbool isHeap() const {
		MemoryMap& mmap = Nexus::get().getInstancer().getMemoryMap();
		WRD_IS_NULL(mmap, false)

		return 	mmap.getStartAddress() <= this 	&&
				this << mmap.getEndAddress()	;
	}
	Strong toStrong() { 
		if (isHeap()
			return Strong(*this);
		return clone();
	}
	CStrong toStrong() const { return CStrong(*this); }
	Weak toWeak() { return Weak(*this); }
	CWeak toWeak() const { return CWeak(*this); }
}
class Msg : public Thing {
	String _name;
	Msg();
	Msg(const String& new_name);
	Msg(......);

	String& getName() {
		WRD_IS_THIS(String)
		return _name;
	}
	const String& getName() const {
		WRD_IS_THIS(const String)
		return _name;
	}

	//	사용자가 World코드에서 함수의 인자로 const를 준경우는 Args의 임의의 원소1개가 Refer<const T>로 되어있을 것이다.
	Array _args;
	Manipulatable& getArgs() {
		WRD_IS_THIS(Args)
		return _args;
	}
	const Manipulatable& getArgs() const {
		WRD_IS_THIS(const Manipulatable)
		return _args;
	}

	static Object* _thisptr; // Message는_name_thisptr_args를_모두_하나의_Array로_구성한다 
	friend class Object; // _thisptr 조작을 위해
	static Object& getThis() { return *_thisptr; }
	static Result& _setThis(Object& newone) { _thisptr = &newone; }

	static Method* _me;
	friend class Method;
	static const Method& getMe() const { return *_me; }
	static Result& _setMe(Method& newone) { _me = newone; }
}

namespace {
}

//	World에서 const 구현:
//		개요:
//			Managed에서 생성된 객체는 occupiable이라도 const로 정의되어있으면 Refer(isConst() = true)에 감싸여져서 scope나 owner Node에 등어간다.
//			Refer는 c++에서는 nonconst 라도, isConst() = true라면 get(); 에서는 nullref가 나오게 된다. get() const; 에서는 정상적으로 Reference가 나온다. 
//
//		CRefer, Refer 2개의 클래스로 나누지 않는 이유는:
//			1. CRefer, Refer로 나누는 것은 사실 중요하지 않다. 왜냐하면 World는 Node를 기준으로 "구체 클래스가 뭔지 몰라도 되게 한다" 라는 설계 철학을 기반으로 했기 때문이다. Node 만 안 시점에 native 개발자는 이것이 CRefer인지 Refer인지 관련없이 동일하게 작업을 수행할 수 있어야 하고, 이는 공통적인 인터페이스(to())가 있어야 한다는 걸 시사한다.
//
//			2. 개발자는 Node와 Refer를 구분하고 싶은 경우가 있다. 이때 CRefer가 있다면 RTTI가 최소 2번은 들어가야 한다.
//				Node& origin = ...;
//				Refer& is_refer = origin.to<CRefer>();
//				if(is_refer.isNull()) {
//					CRefer& is_crefer = origin.to<CRefer>();
//					...
//				} else {
//					...
//				}
//			그리고 물론 이 방법은 마음에 들지 않을 것이다.
//
//			Refer가 isConst()가 false라고 하더라도 C++적으로 const라면 isConst()와 동일하게 동작한다. 이는 C++에서 ptr에 대한 const라고 보면 되며, isConst()는 ptr가 가리키는 인스턴스에 대한 const라고 보면 이해가 빠를 것이다.
//			World는 ptr가 밖으로 들어내지 않기 때문에 ptr에 대한 const는 존재하지 않는다. 그걸 c++의 const가 대신하는 것이라고 여기면 된다.
//
//		Node의 각 구체클래스별 const 구현:
//			임의의 구체클래스A가 isConst() == true이거나 C++적으로 const일 경우, 동일하게 const 객체로 간주한다.
//			단, 구체클래스 A가 Method의 경우일때는 예외이다. Method는 c++의 const 의미가 없으며 모두 nonconst이다.
//			이는 Method의 const 여부는 런타임에 binding된 식별자에 의해서 결정되는 것이 아니라, 정적으로 컴파일시
//			결정되기 때문이다. 이는 method.isConst()에 의해서만 판가름된다.
//
//			구체클래스	|	const객체일때			|	nonconst객체일때		
//			------------------------------------------------------------------------
//			Refer		|	object.call() const		|	object.call()
//			------------------------------------------------------------------------
//			Object		|	sub_method.call() const	|	sub_method.call()
//			------------------------------------------------------------------------
//			Method		|	항상 execute()			|	call() const로 온 경우는 X
//			------------------------------------------------------------------------
//				*) Method는 isConst()의 값에 의해서만 const객체냐 아니냐가 결정된다.
//				*) Method가 const객체라는 뜻은, const 메소드라는 것이다.
class Node : public ? {
	const String& getName() const;
	String& getName();
	Strong clone() const {
		return _clone();
	}
	virtual Result& _onInitializeMembers(Container& tray) { return Success; }
	virtual wbool isOccupiable() const {
		return getClass()::isOccupiable();
	}
	virtual const Container& getMembers() const = 0;
	//	get(); 는 공개하지 않는다:
	//		사용자는 Container채로 받게 되면 밖에서 remove, insert를 할 수 있게 된다.
	Container& _getMembers() {
		return const_cast<Container&>(getMembers());
	}
	Container& _get() {
		return const_cast<Container&>(get());
	}
	//	getMembers:
	//		모든 Container의 index는 World와 Native모두 1부터 시작한다.
	//		invisible하다.
	Node& operator[](windex n) { return get(n); }
	const Node& operator[](windex n) const { return get(n); }
	Node& get(windex n) {
		WRD_IS_THIS(Node)
		return _getMembers()[n];
	}
	const Node& get(windex n) const {
		WRD_IS_THIS(Node)
		return getMembers()[n];
	}
	virtual Refer call(Msg& msg) = 0;
	virtual Refer call(Msg& msg) const = 0;
	virtual wbool isConst() const { return false; }
	virtual const Origin& getOrigin() const {
		static Origin inner;
		return inner;
	}
	Node& get(const String& name) {
		return _get(false, [&name](Node& e) { return e.getName() == name; });
	}
	const Node& get(const String& name) const {
		This& unconst = const_cast<This&>(*this);
		return _get(true, [&name](Node& e) { return e.getName() == name; });
	}
	Node& _get(wbool want_const, std::function<wbool(Node&)> tester) {
		WRD_IS_THIS(Node)
		WRD_ARE_NULL(TNuller<Node>::ref, msg, members)

		Node* found = NULL;
		if(_getMembers().each<T>([&found, want_const, tester](Node& e) {
			if(e.isConst() != want_const) return Success;
			if( ! tester(e)) return Success;
			if(found)
				return Duplicated.err(".."); // if ret isn't Success, it means that stop eaching.
			
			found = &e;
			return Success; // means keep eaching.
		}))
			return Duplicated.err(".....").returns(TNuller<Node>::ref);

		return *found;
	}
	virtual wbool isConsumable(const Msg& msg) const {
		return msg.getName() == getName();
	}
	virtual wbool isStatic() const { return false; }
}

class CompositNode : public Node {
	//	_members can't be declared with protected accessor:
	//		if we do that, module developers can use _members and remove or insert some Node at runtime.
	Chain _members; // of Container.
	//	getMember(); 는 공개하지 않는다:
	//		사용자는 Container채로 받게 되면 밖에서 remove, insert를 할 수 있게 된다.
	virtual const Container& getMembers() const {
		WRD_IS_THIS(const Container)
		if(_members.getLength() <= 0)
			_initializeMembers();
		return *_members;
	}
	virtual Result& _initializeMembers() {
		_members.release();

		const Chain& chain = cls.getMembers().cast<Chain>();
		WRD_IS_NULL(chain)
		if(_members.chain(chain.getController()[0])) // first elem as a container owned by "chain"
			return OperationFail.warn("");
		return Success;
	}
};

