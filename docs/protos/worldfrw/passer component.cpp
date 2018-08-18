class Runnable {
	static const String RUN = "@run"; // 앞에 @를 붙인 이유는 월드 코드상에서 이 함수를 명시적으로 호출 할 수 없게 하기 위해서다. 
	wbool isRunnable(const Msg& msg) const { return msg.getName() == RUN; }
	virtual Result& run(const Msg& msg) const = 0;
};

//	Object는 Members를 가져야 하는데, 여러가지를 고려해야만 한다.
//		1. Class에 속한것(Method + static variable)과 객체에 속한것을 구분해야 한다
//			이는 빠른 Object생성과 메모리 효율을 위해 반드시 필요하다.
//		2. private, public을 구분해야 하는가?
//		3. static을 구분해야 하는가?
//		4. const 와 nonconst를 구분해야 하는가?
//	여기서
class Object : public CompositNode {
	Object() : Super() {
	}

	void _precall(Msg& msg) const {
		Object& old = msg.getThis();
		msg._setThis(*this);
	}
	void _postcall(Msg& msg) const {
		msg._setThis(old);
	}
	virtual Refer call(Msg& msg) {
		_precall(msg);
		Refer ret = Super::call(msg);

		_postcall(msg);
		return ret;
	}
	virtual Refer call(Msg& msg) const {
		_precall(msg);
		Refer ret = Super::call(msg);

		_postcall(msg);
		return ret;
	}
	virtual wbool isConsumable(const Msg& msg) const {
		return	msg.getArgs().getLength() <= 0	&&
				msg.getName() == getName();
	}

	//	객체의 멤버변수:
	//		Object Chain = Method.Member + Method.ObjectVariables.clone().
	//		클래스이 member는 공유되어야 하며, Method의 Object용 member는 객체마다 따로 갖고 있어야 한다.
	//		늦은 초기화:
	//			배경:
	//				_members는 native의 메소드들이나 Managed의 멤버변수를 모아두는, 실질적인 visible 의 한 축을 담당한다. (나머지 한 축은 scope)
	//				문제는 native의 메소드를 visible하게 할때 일어나는데, Native환경에서 사용자가 Object를 상속한 임의의 클래스 A를 지역변수로 생성한 경우, 객체를 사용하기 전에 어딘가에서는 Native메소드들을 담고있는 메타클래스로부터 메소드목록을 객체가 fetching 해야한다.
	//				하지만 이 경우 Object의 생성자에서는 최종 구체클래스 A가 뭔지 모르므로 할 수 없다. 반면 A는 사용자의 클래스이므로, A의 생성자에서도 할 수 없다. (사용자에게 limitation을 거는 꼴이다) 따라서, Member의 늦은 초기화로 이문제를 해결한다.
	//
	//			동작:
	//				늦은 초기화는 "Members에 접근하려면 반드시 getMembers() con
	//				st를 통해야 한다" 를 전제로 하고 있다.
	//				A 생성자안에서 사용자가 사용하든, 밖에서 사용하든 Members를
	//				처음 사용하려고 하는 그 순간, Member가 아직 초기화되지 않은
	//				경우라면 초기화 로직을 먼저 시작한다.
	//
	//				이 방법의 가장 중요한 점은, 외부에서는 처음부터 Members가
	//				채워져 있다고 생각하게 만드는 것이다. 이걸 배신하면 안된다.
	//			Limitation:
	//				생성자 안에서 getMembers()를 호출하면 안된다. 초기화는 1번만 일어난다. 여러번 하게도 할 수 있으나, 그렇게하면 기존의 ObjectVariables를 덮어써야 하므로 어짜피 로직은 망하게 된다.
	//	만약 아래의 함수가 visible이 된다면 어떻게 반환형 const가 전달되지?:
	//		TNativeMethod가 반환형 T = const Container임을 알고있다.
	//		TRefer<const Container> ret = (obj->*fptr)().to<const Container>();
	//		return ret;
	virtual Result& _initializeMembers() {
		WRD_IS_ERR(Super::_initializeMembers())
	
		_getMembers().chain(getClass().getVariables().clone());
		return Success;
	}
	Iterator _getSubContainerHead(windex n) {
		Container& sub = getMembers().toSub<Chain>().getController()[n];
		WRD_IS_NULL(sub, Iterator())

		return sub.getHead();
	}
	CIterator _getSubContainerHead(windex n) const {
		const Container& sub = getMembers().toSub<Chain>().getController()[n];
		WRD_IS_NULL(sub, CIterator())

		return sub.getHead();
	}
	Iterator getSharedHead() {
		return _getSubContainerHead(0);
	}
	CIterator getSharedHead() const {
		return _getSubContainerHead(0);
	}
	Iterator getVariablesHead() {
		return _getSubContainerHead(1);
	}
	Iterator getVariablesHead() const {
		return _getSubContainerHead(1);
	}
	virtual const Origin& getOrigin() const { return getClass().getOrigin(); }
};

class MgdObject : public Object {
	//	TODO:
	//		Object에서 상속한것. Object는 getClass()시 어떤 클래스가 나오는지는 code로 정적으로 박혀져있다. 
	//		그래서 MgdObject는 getClass()시 변수_class에서 반환된다.
    //		MgdClass는 MgdObject를 instaitate()하며, 이때 자신을 obj._class에 할당한다.
	TWeak<const MgdClass> _class;
	virtual const Class& getClass() const { return _class; }
};

//	OccupiableObject는 상속된다:
//		상속이란 부모의 모든 특징을 다 물려받는 것이며, int의 자식클래스는 무엇이 되었건 간에 immutable이 될 수 밖에 없다.
//	실질적인 Occupiable vs Sharable의 동작 차이는 Refer에서 발생한다.
class OccupiableObject : public Object {
};

class Refer : public Node {
	This(const Class& cls = Node::getStaticClass(), wbool want_const = false);
	This(Node& it);
	This(const Node& it);
	This(const This& it);
	This(This& it);

	wbool operator==() const;
	wbool operator!=() const;
	This& operator=(const This& it);
	This& operator=(This& it);
	This& operator=(Node& it);
	This& operator=(const Node& it);
	Node& operator->();
	const Node& operator->() const;
	Node& operator*();
	const Node& operator*() const;

	virtual Refer call(Msg& msg) const { return _bean.call(msg); }
	virtual Refer call(Msg& msg) { return _bean.call(msg); }

	Result& bind(Refer& it) {
		return bind(it.get());
	}
	Result& bind(Node& it) {
		//	NullCheckDelayed 철학에 의해서 WRD_IS_NULL(it)을 하지 않는다. 
		const Class& cls = it.getClass();
		WRD_IS_NULL(cls)
		if( ! cls.isSub(_cls))
			return TypeInvalid.warn("...");

		unbind();
		WRD_IS_ERR(_bean.bind(it))
		_is_const = false;
		return Success;
	}
	Result& bind(const Refer& it) {
		return bind(it.get());
	}
	wbool isBinded();
	operator wbool();
	Result& bind(const Node& it) {
		This& unconst = const_cast<This&>(*this);
		Result& res = unconst.bind(const_cast<Object&>(it));
		WRD_IS_ERR(res)

		_is_const = true;
		return res;
	}
	Result& unbind() {
		Result& res = _bean.unbind();
		WRD_IS_ERR(res)

		_is_const = false;
		return Success;
	}
	Node& get() {
		WRD_IS_THIS(Node)
		if(_is_const)
			return InvalidCall.warn("_is_const").returnNull<Object>();

		return _bean.get();
	}
	const Node& get() const {
		WRD_IS_THIS(const Node)
		return _bean.get();
	}

	virtual const Origin& getOrigin() const {
		if( ! _bean)
			return Super::getOrigin();
	
		return _bean->getOrigin();
	}
	virtual wbool isConst() const { return _is_const; }
	wbool _is_const;
	Strong _bean;
	const Class& _cls;

	virtual Result& assign(const Thing& it) {
		// Null체크는 Thing::assign()에서 한다.
		WRD_IS_ERR(Super::assign(it))

		//	Sharable, Occupiable:
		//		여기서는 실질적인 sharing vs occupying의 동작차이를 만들어내는 곳이다.
		//		Occupiable이라도 const 인 경우에는 인터프리터에 의해서 const Refer에 감싸서 scope나 멤버함수에 들어가게 된다.
		//		또한 이문제는 it이 occupiable인지 sharable인지 구분할 필요가 없다. 오로지 this가 occupiable인지 아닌지만 중요하다.
		if(_cls.isOccupiable()) // Occupiable은 상속이 된다.
		{
			//	이경우 const건 아니건 사실 중요하지 않다. 오직 중요한건 occupiable이면 실제 객체에게 assign을 떠 넘기면 된다는 사실이다.
			Node& bean = get(); // 만약 isConst() 일 경우, 여기서 NULL이 나오게 된다.
			WRD_IS_NULL(bean)
			return bean.assign(it);
		}
	
		//	sharable 이라면 이렇게 간단히 끝난다.
		Refer& refered = it.toSub<This>();
		if(refered.isExist())
			return bind(refered);
		return bind(it.toSub<Object>()); // null이 들어가도 상관없다.
	}

	virtual Node& _toSub(const Class& cls) {
		if( ! _bean ||
			! _bean->isSub(cls))
			return TNuller<Node>::ref;

		return *_bean;
	}
};

//	공통 코드는 모든 기능을,
//	구체 코드는 공통 코드를 상속해놓고 일부 기능만 구체적으로 공개하고 공통코드는 Method hiding으로 숨긴다.
//	CIterator, TWeak와 동일한 구조다.
template <typename T>
class TRefer : public Refer {
	This() : Super(false) {}
	This(T& bean);

	This(const T& bean);
	This(const This& it);

	//	Result& bind(T& it) 를 만들지 않는다. 왜냐하면 Object로 들어와도, 실제로는 T 일 수 있기 때문이다.
	//	operator=도 같다.

	T& get();
	const T& get() const;
};

template <typename T>
class TRefer<const T> : public Refer {
	This() : Super(true) {}
	This(const T& bean);
	This(const This& it);

	operator=(const This& it); // method hiding. TRefer<T>와 다르게 nonconst를 빼야 하므로 은닉한다.
	operator=(const T& it);

	Result& bind(const T& it); // method hiding.
	Result& bind(const Refer& it);

	const T& get() const;
};

//	Usage:
	Refer ref = ....; // const A였을때,
	TRefer<A> noncon = ref;
	nonconst.isBind() // = false
	TRefer<const A> con1 = ref;
	const TRefer<A> con2 = ref;
	ref.isBind() == ref2.isBind() // = false. con2는 nonconst로 바인딩이 1차 시도되고, 실패되므로.
	TRefer<const A> con3(A());
	A a;
	const A& ca = a;
	con3.bind(a); // err.
	con3.bind(ca);
	noncon.bind(a);
	con3 = noncon; // ok. but bind failed at runtime.
	con3.isBind(); // false
	A& out1 = con3.get(); // err. con3.get() returns type of const A&
	const A& out2 = con3.get(); // ok, however...
	out2.isNull(); // true
	const TRefer<A> con4(A());
	const A& out3 = con4.get(); // ok. con4 has get() nonconst method, but get() const method is only accessable.
	con4 = con3 // ok
	con4.isExist() // false

class MethodDelegator : public TRefer<Method>, public Runnable {
	//	captures:
	//		The Captures are captured from the localspace and classspace 
	//		when a instance of this class born.
	mutable TStrong<Object> _this;
	mutable TStrong<Array> _captures; // we should have perfect cloned array which contains each shallow copied instance from the original.
	Object& getThis() { return *this; }
	const Object& getThis() const { return *this; }
	const Array& getCaptures() const {
		WRD_IS_THIS(const Array)
		return _captures;
	}

	virtual wbool isConsumable(const Msg& msg) {
		wbool ret = Super::isConsumable(msg);
		if(ret)
			_captureLocals();
		return Super::call(msg); // TODO: msg is const instance.
	}

	Result& _captureLocals() {
		if(_captures.getLength() > 0)
			return alreadydone;
		return _captures.bind(scope.getControl().getLocals().deepclone()); // Containable --implicitCasting--> Array at inside of _captures.
	}

	virtual Result& run(const Msg& msg) const {
		if( ! isBind()) return notbind.warn()
		if( ! _this) return get().run(msg);

		Scope::Spaces& spaces = scope.getControl();
		TStrong<Array> locals = spaces.getLocals();
		TStrong<Chain> classs = spaces.getClasss();
		spaces.setLocals(_captures);
		sapces.setClasss(_this->getMembers());

		Result& res = get().run(msg);

		spaces.setLocals(*locals);
		spaces.setClasss(*classs);
		return res;
	}
};

typedef TArray<Class> Classes;

typedef TArray<Method> Methods;
//	Method는 Stmt가 될 수 없다:
//		1. Stmt는 처음에 인풋이 들어가고 나서부터는 execute()라는 단순한 함수만으로도 동작이 되어야 한다.
//		메소드는 인자를 그때그때받아야 하므로 적합하지 않다.
//		2. Method가 Stmt라면 블록문 안에 Method가 있을 수도 있어야 한다. 말이 안되지.
//		3. 모든 Method가 BlockStmt를 가지는 것은 아니다. 오직 ManagedMethod만 BlockStmt를 갖는다.
class Method : public Object, public Runnable {
	Classes _params;
	const Classes& getParams() const { 
		WRD_IS_THIS(const Classes)
		return _params;
	}
	virtual Refer call(Msg& msg) {
		if(isRunnable(msg))
			return run(msg);
			
		return Super::call(msg);
	}
	virtual Refer call(Msg& msg) const {
		if(isRunnable(msg())
			return run(msg);
			
		return Super::call(msg);
	}
	//	execute와 run은 다르다:
	//		execute는 인자를 받지 않는다. 그래서 여기서는 run이라는 함수로 구분할 수 밖에 없었다.
	virtual Refer run(const Msg& msg) {
		if(isConst()) // const 방어.
			return NotAllow.warn("...").returns<Refer>();

		const This* consted = this;
		return consted->run(msg);
	}
	virtual Refer run(const Msg& msg) const {
		if( ! isRunnable(msg)) {
			WrongParam.warn()
			return Refer();
		}

		windex boundary = locals.getLength();
		TStrong<Method> origin;
		_stack(scope, origin);

		This* unconst = const_cast<This*>(this);
		Refer ret = unconst->_onRun(msg);

		_unstack(scope, boundary, origin);
		return ret;
	}
	//	ready CallStack:
	virtual Result& _stack(Scope& scope, TStrong<Method>& origin) const {
		origin = scope.getMe();
		return scope.setMe(*origin);
	}

	virtual Result& _unstack(Scope& origin, windex boundary, const TStrong<Method>& origin) const {
		Array& locals = scope.getControl().getLocals();
		while(locals.getLength() > boundary)
			locals.deq();
		return scope.setMe(*origin);
	}

	virtual Refer _onRun(const Msg& msg) = 0;
	virtual wbool isConsumable(const Msg& msg) const {
		Args& args = msg.getArgs();
		const Classes& params = getParams();
		//	case 1: when user try to let this consume msg as a class.
		if(msg.getName() == getName())
			return args.getLength() <= 0;
		//	case 2: consume as a method.
		if(msg.getName() != RUN)
			return false;
		if(args.getLength() != params.getLength()) 
			return false;

		for(int n=0; n < args.getLength(); n++)
			if( ! args[n].to(params[n]).isBind())
				return false;
		return true;
	}
	//	오직 메소드만 Static여부를 반환한다:
	// 		Variable의 static여부는 판단이 불가능하다. Managed는 가능한데, Native로 static MyObject my; 처럼 만든 variable은 불가능하기 때문이다.
virtual bool isStatic() const { return false; }
};



class MgdMethod: public Method {
	//	NestedMethods only can exists on method on Managed env:
	Methods _nested_methods;
	const Methods& getNestedMethods() { return _nested_methods; }
	TStrong<Origin> _origin;
	virtual const Origin& getOrigin() { return *_origin; }

	virtual Result& _stack(Scope& scope, TStrong<Method>& origin) const
	{
		if(Super::_stack(scope, origin))
			return superfail.warn("");

		Array& locals = scope.getControl().getLocals();
		locals.enq(getArgs();
		return locals.enq(getNestedMethods());
	}

	BlockStmt _block;
	virtual Refer _onRun(const Msg& msg) {
		// TODO: do something with scope obj.
		return _block.execute();
	}
	virtual bool isStatic() const {
		// TODO:
	}
};

class BlockStmt : public Stmt {
	typedef vector<Stmt> Stmts; // stmts은 invisible하게 한다는 뜻이다.
	tStmts _stmts;
	Stmts& getStmts();
	const Stmts& getStmts() const;
	virtual Result& execute() const {
		for(auto s in _stmts)
			s.execute();
		return Success;
	}
};

//	요구조건:
//		[] execute()시, owner가 없다면 실행해서는 안된다. (= 런타임에 간접적인 로직 변경 방지)
class Stmt : public Object {
	TStrong<Origin> _origin;
	virtual const Origin& getOrigin() { return *_origin; }
	virtual const Result& execute() = 0;
	virtual const Container& getMembers() {
		return getClass().getMembers();
	}
};

//	Expression은 invisible 하다.
class Expr : public Stmt {
	Msg _msg;
	const Msg& getMsg() const;
	Msg& getMsg();

	TStrong _caller; // expression or object 가 여기에 들어간다.
	Node& getCaller();
	const Node& getCaller() const;

	virtual Result& execute() const; // const 상태에서도 excute가 가능하게 해야한다.
	// Expression은 반환형이 될 수 없다는 것이다.
	// visible할 필요가 없으므로 Refer로 하지 않는다.
	mutable TStrong _returned; 
	Node& getReturned() const;

	virtual Refer to(const Class& cls) const {
		if(cls.isSub(Node::getStaticClass())) 
		{
			execute();
			return Refer(cls, _returned);
		}

		return Super::to(cls);
	}
};
