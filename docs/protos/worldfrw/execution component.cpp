class InstanceBlock : public Thing {
	friend class Weak;
	//	_strong을 위해서다.
	wcount getCount() const { return _strong; }
	Result& _increaseCount() {
		_strong++;
		return Success;
	}
	Result& _decreaseCount() {
		if(--_strong <= 0)
			release();
		return Success;
	}
	//	Strong reference 카운트다.
	wcount _strong;
	Instance& get();
	const Instance& get() const;
	Result& release();
};


//	Scope:
//		요구사항:
//			외부공개 규칙:
//				값 변경은 불가능:
//				validation을 유지하기 위해서 절대로 native든 managed든 scope의 존재나 간접적인 조작이 가능해서는 안된다.
//				간접적인 조작의 예) 변수를 정의하는 Stmt를 지역변수로 만들어 바로 execute() 함.
//
//				값 read는 가능:
//				IDE등에서 콜 스택의 목록을 보여주는 용도로 사용가능해야 하므로 무슨 값이 있는지는 알 수있어야 한다.
//				결과적으로 Scope 클래스는 const로써만 manager에서 제공된다.
//
//		등록:
//			Object를 "어떻게" 등록하는 가는 Object에서 정해야한다. Object에서 Scope는 사용할 수 있는 도구로써만 존재해야 한다.
//
//				Object: ObjectSpace를 교체한다. Scope에 members를 등록한다. call이 끝나면 members와 그 사이에 존재하는 모든 symbol을 모두 해제 한다. Object 단위로, push remote가 이루어지며, stack의 형태로 Object의 멤버가 쌓여져야 한다. ObjectSpace는 visible 영역이 존재해서 stack 처럼 되어 있어도 항상 [0] 원소인 Object의 공간만 visible 해야 한다.
//				Method: LocalSpace를 교체한다. 그리고 execute가 발생하면 arguments와 static, nested method를 members에 등록한다. 메소드가 끝나면 그 동안 Expr에 등록된 모든 지역변수들을 제거 한다.
//				NestedMethod: LocalSpace교체 없다. execute가 발생하면 arguments와 static, nested method를  mebers에 등록한다.
//				Expr: 지역변수를 Scope에 등록한다.
//
//			최적화 과정 때문에FIFO로 인덱싱되어야 한다. (마지막에 들어온건 항상 0이어야 한다)
//			이렇게하면 어느 상황에서 실행하건간에 ObjectSpace와 LocalSpace의 요소들의 index는 항상 런타임시 동일하게 된다
//			어떠한 상황에서도 scope에 들어가있는 식별자가 중복되는 일은 없어야 한다. 중복이 감지되면 바로 에러를 리턴한다.
//			또한 scope는 이름을 통해서 식별자 찾기를 요청받은 경우, validation으로 간주하고 모든 members를 탐색해야만 한다.
//		
//		예제:
//			Control: Space를 제어한다.
//				//	Scope 자체는 World frx 안에서 제한된 클래스 안에서만 사용이 가능하다.
//				//	또한 Control를 얻어와서 scope의 배열의 원소인 space를 바꾸는 것은 권장되지 않는다. 
//				//	가능하면 set으로 교체만 해야 한다.
//				Control& con = scope.getControl().set(1, Chain());
//				Strong backup = scope.getClassSpace();
//				scope.getClassSpace() = backup
//
//				//	그러나 space 자체에 무언가를 추가하는 것은 권장된다.
//				scope.enq(...); // FIFO로 항상 구성되어야 하므로 push가 아니라 enq를 해야한다.
class Scope : public Chain { // Scope는 visible할 수 있으나 invisible로 된다. mappingtable에 등록하지 않는다.
	friend class Object;
	friend class Method;

	static const int LOCAL = 0;
	static const int CLASS = 1;
	static const int GLOBAL = 2;
	class Spaces : public Chain::Control {
		Array& getGlobals() { return get(GLOBAL);
		const Array& getGlobals() const { return get(GLOBAL); }
		Result& setGlobals(Array& newone) { return set(GLOBAL, newone); }

		Chain& getClasss() { return get(CLASS); } // getClassSpace()
		const Chain& getClasss() const { return get(CLASS); }
		Result& setClasss(Chain& newone) { return set(CLASS, newone); }

		Array& getLocals() { return get(LOCAL); }
		const Array& getLocals() const { return get(LOCAL); }
		Result& setLocals(Array& newone) { return set(LOCAL, newone); }
	};
	Spaces& getControl() { return Super::getControl().down<Spaces>(); }
	const Spaces& getControl() const { return Super::getControl().down<Spaces>(); }

	virtual TStrong<Control> _onCreateControl(Chain& origin) { return new Spaces(origin); }
	virtual Result& initialize() {
		if(Super::initialize()) // it will call release().
			return supererr.warn();

		Chain::Control& con = getControl();
		con.push(Array());	//	LocalSpace
		con.push(Chain());	//	ClassSpace
		con.push(Array());	//	GlobalSpace
		// elements는 절대 remove 되어서는 안된다. Scope의 모든 함수는 항상 원소3개가 있다고 가정한다.
		return Success;
	}

	using Super::get;
	Node& get(const String& name) {
		WRD_IS_THIS(Node)
		Node& res = ....;
		return _filterConst(res);
	}
	Node& _filterConst(Node& it) {
		if(_is_obj_const && ! it.isConst())
			return nullreference<Node>();
		return it;
	}
	const Node& get(const String& name) const {
		This& cast = const_cast<This&>(*this);
		return cast.get(n);
	}
	Node& operator[](const String& name) { return get(name); }
	const Node& operator[](const String& name) { return get(name); }
	Node& get(windex n) {
		WRD_IS_THIS(Node)
		Node& res = ...;
		return _filterConst(res);
	}
	const Node& get(windex n) const {
		This& cast = const_cast<This&>(*this);
		return cast.get(n);
	}
	Node& operator[](windex n) { return get(n);
	const Node& operator[](windex n) const { return get(n); }
	virtual Result& release();

	virtual Result& insert(....); // LocalSpace에만 insert가 되어야한다.
	Result& replace(....); // 없을때는 insert. 있으면 set.
	virtual Result& remove(......);

	Result& stack(Object& thisptr) {
		getControl().set(CLASS, thisptr.getMembers());
		replace("this", thisptr);
		// TODO: 나중에 unstackObject을 위해서 큐를 가지고 있어야 한다. 복원해줘야 함. this도.
		
	}
	Result& stack(const Object& thisptr) {
		Result& res = stack(const_cast<Object&>(thisptr));
		if(res)
			return failsuper;
		_is_obj_const = true;
		return res;
	}
	Result& stack(Method& me) {
		// TODO: unstackMethod() 했을때를 대비해서 어디 index까지 pop해야 하는지 알고 있어야 한다. me도 복원해야 함.
		replace("me", me);
	}
	Result& unstack(Object&/*only used for distinguish method and object*/) {
		// TODO: object queue를 pop해서 이전에 두고 있던 objectspace로 복귀해야 한다.
		_obj.release();
		_is_obj_const = false;
	}
	Result& unstack(Method& me);

	Result& _release() {
		return _unstack(nullreference<Object>());
	}

	TWeak<Object> _obj;
	wbool _is_obj_const;
};

//	요구조건:
//		[] execute()시, owner가 없다면 실행해서는 안된다. (= 런타임에 간접적인 로직 변경 방지)
//	Expression은 invisible 하다.
//	Static method call에 해당하는 것을 담당한다.
class Expr : public Node {
	TStrong<Origin> _origin;
	virtual const Origin& getOrigin() { return *_origin; }
	virtual const Container& getMembers() {
		return getClass().getMembers();
	}

	Refer _caller; // expression or object 가 여기에 들어간다. isConst()여부를 따져야 하기 때문에 TStrong은 될 수 없다.
	Refer& getCaller();
	const Refer& getCaller() const;

	mutable Msg _msg;
	Msg& getMsg();
	const Msg& getMsg() const;

	virtual Refer execute() { 
		if( ! _caller)
			return Refer();

		// 이 함수는 nonconst이기 때문에 _caller로부터 나온 Node는 nonconst이며, nonconst call은, isConst() 여부에
		// 따라서 적절한 값이 실행되게 된다.
		return _caller->call(_msg); // 놀랍게도 이 1줄만으로도 모든게 끝난다.
	}
	virtual Refer execute() const { 
		if( ! _caller)
			return Refer();

		return _caller->call(_msg); // execute() nonconst와는 코드를 합칠 수 없다. 여기의 _caller가 const냐 아니냐가 중요학 ㅣ때문이다.
	}
	virtual Refer call(Msg& msg) { return execute(); }
	virtual Refer call(Msg& msg) const { return execute(); }

	virtual Refer to(const Class& cls) const {
		if(cls.isSub(Node::getStaticClass())) 
			return execute();

		return Super::to(cls);
	}
};

class ThisExpr : public Expr {
	virtual Refer execute() {
		_msg.push(_caller);
		Refer ret = Super::execute();
		_msg.pop();
		return ret
	}

	virtual Refer execute() const {
		_msg.push(_caller);
		Refer ret = Super::execute();
		_msg.pop();
		return ret
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

