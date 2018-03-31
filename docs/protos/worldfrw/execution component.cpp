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
//				Object: Scope에 members를 등록한다. call이 끝나면 members와 그 사이에 존재하는 모든 symbol을 모두 해제 한다. Object 단위로, push remote가 이루어지며, stack의 형태로 Object의 멤버가 쌓여져야 한다. ObjectSpace는 visible 영역이 존재해서 stack 처럼 되어 있어도 항상 [0] 원소인 Object의 공간만 visible 해야 한다.
//				Method: arguments와 static을 members에 등록한다. 메소드가 끝나면 그 동안 Expr에 등록된 모든 지역변수들을 제거 한다.
//				Expr: 지역변수를 Scope에 등록한다.
//			최적화 과정 때문에FIFO로 인덱싱되어야 한다. (마지막에 들어온건 항상 0이어야 한다)
//			이렇게하면 어느 상황에서 실행하건간에 ObjectSpace와 LocalSpace의 요소들의 index는 항상 런타임시 동일하게 된다.
//		
//		예제:
//			Control: Space를 제어한다.
//				Control& con = Scope.getControl();
//				con.insert(Scope::INDEX_OBJECT_SPACE, obj.getMembers());
//				con.remove(1);
//
//				con.pop(); // LocalSpace 초기화.
//				con.push(....); // OBJECT_SPACE를 제외한 인덱스에는 control로 데이터를 넣을 수 없다.
class Scope : public Chain { // Scope는 visible할 수 있으나 invisible로 된다. mappingtable에 등록하지 않는다.
	static const wcount MAX_LENGTH = 3;
	static const windex INDEX_GLOBAL_SPACE = 0;
	static const windex INDEX_OBJECT_SPACE = 1;
	static const windex INDEX_LOCAL_SPACE = 2;

	friend class DefineVariableStmt; // 변수 정의
	friend class Method;
	friend class Object;
	friend class ScopeControl;

	Array _globals; // global space
	Array _locals; // local space
	typedef TArray<TStrong<Chain> > ObjectSpace;
	ObjectSpace _objects;

	virtual Result& initialize() {
		release();
		_globals = TClass<Array>::instantiate();
		_locals = TClass<Array>::instantiate();
		_objects.push(TStrong<Chain>()); // push a vacant.

		Chain::Control& con = getControl();
		con.push(_globals);
		con.push(*_object[0]);
		con.push(_locals);	//	elements는 절대 remove 되어서는 안된다. 
							//	Scope의 모든 함수는 항상 원소3개가 있다고 가정한다.
		return Success;
	}

	virtual TStrong<Control> _onCreateControl(Chain& owner) {
		class ScopeControl : public TControl<Scope> {
			This(Chain& owner);
			
			virtual Result& insert(const Iterator& pos, const Node& it) { // it == Chain
				Scope& origin = getOrigin();
				WRD_IS_NULL(origin, nullref)

				windex n = pos.toIndex();
				switch(n)
				{
					case INDEX_OBJECT_SPACE:
						if(origin._objects.push(it.toStrong()))
							return opfail.err();
						return Super::insert(pos, it);

					case INDEX_LOCAL_SPACE:
					case INDEX_GLOBAL_SPACE:
						return notpermit.warn("");
				}	
				return outbound.err();
			}

			virtual Result& remove(const Iterator& pos) {
				Scope& origin = getOrigin();
				WRD_IS_NULL(origin, nullref)
	
				windex n = pos.toIndex();
				switch(n)
				{
					case INDEX_OBJECT_SPACE:
						...do something..

					case INDEX_LOCAL_SPACE:
						//	여기서 Super::remove()를 호출하면 안된다:
						//		Scope는 항상 원소3개가 유지되어야 하기 때문이다.
						//		여기서는 Super[INDEX_LOCAL_SPACE]에 해당하는 _locals를 바로 비워주기만 하면 된다.
						return origin._locals.release();

					case INDEX_GLOBAL_SPACE:
						return origin._globals.release();
				}

				return outbound.err();
			}
		};
		return new ScopeControl(owner);
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

	Result& enroll(Node& it) {
		
	}

	virtual Result& release();
};
