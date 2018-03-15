class Executable {
	virtual Result& execute() const = 0;
};

//	Object는 Members를 가져야 하는데, 여러가지를 고려해야만 한다.
//		1. Class에 속한것(Method + static variable)과 객체에 속한것을 구분해야 한다
//			이는 빠른 Object생성과 메모리 효율을 위해 반드시 필요하다.
//		2. private, public을 구분해야 하는가?
//		3. static을 구분해야 하는가?
//		4. const 와 nonconst를 구분해야 하는가?
//	여기서
class Object : public Node {
	virtual Refer call(const Msg& msg) {
		Object& old = msg.getThis();
		msg._setThis(*this);

		...

		msg._setThis(old);
	}
	virtual Refer call(const Msg& msg) const {
	}
};

//	OccupiableObject는 상속된다:
//		상속이란 부모의 모든 특징을 다 물려받는 것이며, int의 자식클래스는 무엇이 되었건 간에 immutable이 될 수 밖에 없다.
//	실질적인 Occupiable vs Sharable의 동작 차이는 Refer에서 발생한다.
class OccupiableObject : public Object {
	virtual wbool isOccupiable() const { return true; }
};

class Refer : public Node {
	This(const Class& cls = Node::getStaticClass(), wbool want_const = false);
	This(Object& it);
	This(const Object& it);
	This(const This& it);

	operator==() const;
	operator!=() const;
	operator=(const This& it);
	operator=(Object& it);
	operator=(const Object& it);
	Object& operator->();
	const Object& operator->() const;
	Object& operator*();
	const Object& operator*() const;

	virtual CStrong call(const Msg& msg) const { return _bean.call(msg); }
	virtual Strong call(const Msg& msg) { return _bean.call(msg); }

	Result& bind(Refer& it) {
		return bind(it.get());
	}
	Result& bind(Object& it) {
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
	Result& bind(const Object& it) {
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
		WRD_IS_THIS(Object)
		WRD_IF(_is_const, InvalidCall, Nuller<Object>::ref)

		return _bean.get();
	}
	const Node& get() const {
		WRD_IS_THIS(Object)
		return _bean.get();
	}

	wbool isConst() const { return _is_const; }
	wbool _is_const;
	TStrong<Node> _bean;
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
		Refer& refered = it.subcast<This>();
		if(refered.isExist())
			return bind(refered);
		return bind(it.subcast<Object>()); // null이 들어가도 상관없다.
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

	operator=(const This& it);
	operator=(T& it);

	Result& bind(T& it);
	Result& bind(Refer& it);

	T& get();
	const T& get() const;
};

template <typename T>
class TRefer<const T> : public Refer {
	This() : Super(true) {}
	This(const T& bean);
	This(const This& it);

	operator=(const This& it); // method hiding
	operator=(const T& it);

	Result& bind(const T& it); // method hiding
	Result& bind(const Refer& it);

	const T& get() const;
};

//	Usage:
//		Refer ref = ....; // const A였을때,
//		TRefer<A> noncon = ref;
//		nonconst.isBind() // = false
//		TRefer<const A> con1 = ref;
//		const TRefer<A> con2 = ref;
//		ref.isBind() == ref2.isBind() // = false. con2는 nonconst로 바인딩이 1차 시도되고, 실패되므로.
//		con1.get()

class Method : public Object, public Executable {
	BlockStmt _blkstmt;
	virtual Result& execute() const {
		Method& old = msg.getMe();
		msg._setMe(*this);

		...

		msg._setMe(old);
	}
};

class BlockStmt : public Stmt {
	typedef vector<Stmt> Stmts;
	Stmts _stmts; // Expr은 invisible하게 한다는 뜻이다.
	Stmts& getStmts();
	const Stmts& getStmts() const;
	virtual Result& execute() const {
		for(auto s in _stmts)
			s.execute();
		return Success;
	}
};

class Stmt : public Instance, public Executable {};

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
