class Thing {
	//	Thing은 World의 최상위 객체
	virtual Result& release();
	template <typename T, typename S>
	friend class TVisitation;
	//	_tour를 위한 것이다.
	wbool isNull() const { return !this; }
	wbool isExist() const { return this; }
	virtual Result& _tour(Visitor& visitor) const { return Success; }
	//	Visitor에 의해서 하위 구성요소(ownee)들을 어떻게 순회시킬지를 정한다.
	virtual Result& _tour(Visitor& visitor) {
		const This* consted = const_cast<const This*>(this);
		return consted->_onTour(visitor);
	}
	virtual wbool isSuper(const Class& it) const {
		return getClass().isSuper(it);
	}
	wbool isSuper(const Thing& it) const {
		return getClass().isSuper(it.getClass());
	}
	template <typename T>
	wbool isSuper() const {
		return getClass().isSuper(T::getStaticClass());
	}
	wbool isSub(const Thing& it) const {
		return it.getClass().isSuper(getClass());
	}
	wbool isSub(const Class& it) const {
		return it.isSuper(getClass());
	}
	template <typename T>
	wbool isSub() const {
		return T::getStaticClass().isSuper(getClass());
	}
	const Class& getClass();
	virtual Refer to(const Class& cls) {
		return Refer();
	}
	Refer to(const Class& cls) const {
		This& unconsted = const_cast<T&>(*this);
		wbool should_const = cls.isSuper(getClass());
		return Refer(unconsted.to(cls), should_const);
	}
	template <typename T>
	TRefer<T> to() {
		return Refer<T>(to(T::getStaticClass()));
	}
	template <typename T>
	TRefer<T> to() const {
		return Refer<T>(to(T::getStaticClass()));
	}

	//	구체클래스로 자동 캐스트한다. dynamic_cast와 동급이다.
	//	invisible이다.
	template <typename T>
	T& subcast() {
		if(isSub(T::getStaticClass()))
			return (T&) *this;
		return TNuller<T>::ref;
	}

	//	가상할당자이다. 할당연산자는 virtual이 안되기 때문에 제대로 할당을 하고 싶다면 항상 구체타입을 알고 있어야만 한다.
	virtual Result& assign(const Thing& it) {
		if(it.isNull()) return NullError;
	}
}
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

	virtual TStrong<?> clone() const;
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
}
class Msg : public Thing {
	String _name;
	String& getName() {
		WRD_IS_THIS(String)
		return _name;
	}
	const String& getName() const {
		WRD_IS_THIS(const String)
		return _name;
	}

	Args _args;
	Args& getArgs() {
		WRD_IS_THIS(Args)
		return _args;
	}
	const Args& getArgs() const {
		WRD_IS_THIS(const Args)
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
class Node : public ? {
	virtual wbool isOccupiable() const { return false;/*default*/ }
	virtual const Container& getMembers() const = 0; // invisible
	Container& _getMember() {
		return const_cast<Container&>(getMember());
	}
	//	getMembers:
	//		모든 Container의 index는 World와 Native모두 1부터 시작한다.
	//		invisible하다.
	Node& operator[](windex n) { return getMember(n); }
	const Node& operator[](windex n) const { return getMember(n); }
	Node& getMember(windex n) {
		WRD_IS_THIS(Node)
		return _getMembers()[n];
	}
	const Node& getMember(windex n) const {
		WRD_IS_THIS(Node)
		return getMembers()[n];
	}
	virtual wbool isConsumable(const Msg& msg) const { return false; }
	virtual Refer call(const Msg& msg) { return _call<This>(msg, getMembers()); }
	virtual Refer call(const Msg& msg) const { return _call<const This>(msg, _getMembers()); }
	template <typename T, typename S>
	Refer _call(const Msg& msg, S& members);
}
	//	implement this only inside of cpp file
	template <typaname T, typename S>
	Refer Node::_call(const Msg& msg, S& members) {
		WRD_IS_NULL(msg)
		WRD_IS_NULL(members)

		T* found = NULL;
		if(members.template each<T>([&found, &msg](T& e) {
			if(e.isConst() != TConstChecker<T>::IS)
				continue;
			if( ! e.isConsumable(msg))
				return Success;
			if(found)
				return Duplicated.err(".."); // if ret isn't Success, it means that stop eaching.
			
			found = &e;
			return Success; // means keep eaching.
		}))
		{
			Duplicated.err(".....");
			return Refer();
		}

		return found->call(msg);
	}
