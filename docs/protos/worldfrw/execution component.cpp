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
	Array _globals; // global space
	Array& getGlobalSpace();
	const Array& getGlobalSpace() const;

	TStrong<Chain> _classs; // class space
	TStrong<Chain>& getClassSpace();
	const TStrong<Chain>& getClassSpace() const;

	TStrong<Array> _locals;
	TStrong<Array>& getLocalSpace();
	const TStrong<Array>& getLocalSpace() const;

	Result& setThis(Object& new_this);
	Node& getThis();
	const Node& getThis() const;
	Result& setMe(Method& new_me);
	Method& getMe();
	const Method& getMe() const;

	virtual Result& initialize() {
		release();
		_locals = TClass<Array>::instantiate();

		Chain::Control& con = getControl();
		con.push(_globals);
		con.push(*_classs);
		con.push(*_locals);	//	elements는 절대 remove 되어서는 안된다. 
							//	Scope의 모든 함수는 항상 원소3개가 있다고 가정한다.
		return Success;
	}

	using Super::get;
	Node& get(const String& name) {
		WRD_IS_THIS(Node)
	}
	const Node& get(const String& name);
	Node& operator[](const String& name) { return get(name); }
	const Node& operator[](const String& name) { return get(name); }
	Node& get(windex n);
	const Node& get(windex n);
	Node& operator[](windex n) { return get(n);
	const Node& operator[](windex n) const { return get(n); }
	virtual Result& release();
};
