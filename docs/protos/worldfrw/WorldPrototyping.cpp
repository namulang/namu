namespace wrd
{
	//	typedef들:--------------------------------------------
	typedef int wid;
	typedef int wint;
	typedef bool wbool;
	typedef int wcnt;
	class Result;
	template <typename S, typename T> class Bind;
	class Strong;
	class Weak;
	class Node;
	class Object;


	class Thing {
    public:
        virtual Result& release() = 0;
		//dump?
		virtual const Visitor& tour(Visitor& visitor) const = 0;
    };

	class Instance : public Thing { // Instance 관리가 가능함.
		//	w로 시작하는 작은 타입def는 primitive에 대한 typedef를 의미한다. 객체가 아니다.
		wid getId() const;
		wid _id;

		//	World에는 c++ Native의 method만 visible하게 할 수 있다. (limitation)
		//		왜냐하면:
		//			1. 객체마다 visible하게 하려면 proxy를 만들어둬야한다. 추가적인 퍼포먼스 & 메모리를 요구한다.
		//			2. 변수를 그대로 제공해야만 하는 경우는 없다. 메리트가 없는 것이다.
		virtual const Result& assign(const Thing& rhs) {
			if(Super::assign(rhs)) return SuperExcept();

			This::operator=(rhs);
			return Success;
		}
		virtual Strong clone() = 0;
		template <typename T>
		TStrong<T> to() { return to(TClass<T>()); }
		virtual Result& assign(const Thing& rhs) {
			if(!rhs.isSubOf(*this)) return TypeExcept();

			This::operator=(rhs);
			return Success;
		}
		virtual Visitor& tour(Visitor& visitor) const {
			return Super::tour(visitor)
				.visit("_id", _id)
				...
		}
	};

	/*	왜 operator=는 virtual이 될 수 없는가?
	 *	다형성은 act하는 쪽에서 다양한 동작을 융통성있게 흡수하기 위한것이다.
	 *  반대로 말하면 인자는 항상 동일하다. 그러나 operator=는 어떤가. act와 인자가 모두 그때그때 달라야한다.
	 *  즉, virtual assign() 같은 걸 만들어서 operator=대신 하려고 한다면 항상 타입캐스팅이 필요로 하게 된다.
	 */







	/////////////////////////////////////////////////////////////////
	//	Container컴포넌트:------------------------------------------
	//		Container는 주의할것이, C++을 위한 것이 아니라 월드를 위한 Conatiner이라는 점이다. 그래서 기본타입이 무조건 Node이다.
	//		Container는 Node만을 다루기 때문에 각 원소들은 heap에 있는 것이다.
	class Iterator : public Object {
		class Iteration : public Instance {
			virtual const Result& move(wcnt step) = 0;
			virtual Node& get() = 0;
			virtual wbool isEnd() const = 0;
			TWeak<Container> 
		};
	};
	class Container : public Object, public Containable {
		virtual Result& insert(const Iterator& pos, const Node& trg) = 0;
		Result& insert(widx n, const Node& trg);
		Result& insert(const Iterator& pos, const Iterator& rhs_start, const Iterator& rhs_end);
		Result& insert(widx n, const Iterator& rhs_start, const Iterator& rhs_end);
		Result& insert(const Iterator& pos, iterator from stl)
		Result& insert(widx n, iterator from stl...)
		template <typename... Ts>
		Result& insert(const Iterator& pos, Ts... args) {
		}
		template <typename... Ts>
		Result& insert(widx n, Ts... args) {
			return insert(getIterator(n), args...);
		}

		widx push(const Node& trg); // returns push하고 난 뒤의 index
		widx push(const Iterator& rhs_start, const Iterator& rhs_end);
		widx push(iterator from stl)
		template <typename... Ts>
		widx push(Ts... args) {
			return insert(getTail(), args...);
		}

		virtual Result& remove(const Iterator& pos, const Node& trg) = 0;

		virtual Node& _get(const Iterator& pos) = 0;

		wcnt getLength() const { return _length; }

		virtual Node& get(widx n) { return getIterator(pos).get(); }
		const Node& get(widx n) const;
		virtual Iterator getIterator() = 0;
		virtual CIterator getIterator() const = 0;
		Iterator getTail();
		CIterator getTail() const;
		Iterator getHead();
		CIterator getHead() const;
		virtual Iteration& _onCreateIteration() = 0;
		Result& each(const Method& lambda);
		template <typename T>
		Result& each(T lambda);
		// 삽입가능한 타입을 말한다.
		// 생성시 한번 정해지면 변경이 불가능해야 한다.
		virtual Class& getTrait() { return TClass<Node>(); }

	protected:
		wcnt _length;
	};
	class SolidContainer : public Container {
		wcnt getSize() const { return _size; }
		virtual wcnt resize(wcnt newsize) = 0;

	protected:
		wcnt _size;
	};
	class Array : public SolidContainer {
		Array();
		template <typename... Ts>
		Array(Ts... args) { // Ts is SubOf Node.
			std::initializer_list<Node*> tray = {&args...};
			push((*e)->begin(), (*e)->end());
		}
		
		virtual TStrong<Iteration> _onCreateIteration() {
			class ArrayIteration: public Iteration {
			};
			return TStrong<Iteration>(new ArrayIteration(*this));
		};
		/* TODO:
		 * The way to make a for(:) loop work on your type X is now one of two ways:
		 * Create member X::begin() and X::end() that return something that acts like an iterator
		 * Create a free function begin(X&) and end(X&) that return something that acts like an iterator, in the same namespace as your type X.¹
		 */
	};
	class List : public Container {
	};
	class Cell : public SolidContainer {
	};

	class Chain : public TCell<Container> {
		//	Control을 사용해서 Chain의 element인 Container들을 조작할 수 있다.
		class Control : public Container {
		};
	};

	template <typename S, typename T>
	class TContainer : public S {
		T& get(const Iterator& pos);
		virtual Class& getTrait() { return TClass<T>(); }
	};
	template <typename T>
	using TArray = TContainer<Array, T>;
	template <typename T>
	using TList = TContainer<List, T>;
	template <typename T>
	using TCell = TContainer<Cell, T>;
	/////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////








	/////////////////////////////////////////////////////////////////
	//	MetaClass 컴포넌트	---------------------------------------
	/////////////////////////////////////////////////////////////////
	class Type : public Object {
	};
	typedef TArray<Class> Classes;
	class Class : public Type {
		virtual const String& getName() const { return _name; }
		virtual const Classes& getSupers() const;
		virtual const Classes& getSubs() const;
		// 모든 sub들 중에서 sub가 없는 leaf 노드들만 반환한다.
		const const Classes& getLeafs() const;
		//	Shared Members: 모든 객체마다 share하는 클래스의 멤버들. 공유변수 및 Method가 여기에 속한다
		const Members& getShares() const { return _shares; }
		//	(Object) Dependent Members: 객체에 종속되는 멤버들. 객체마다 서로 다른 값을 갖는 멤버들로, 멤버변수가 여기에 속한다.
		const Members& getDependents() const { return _deps; }
		virtual Strong instantiate() const = 0;
		template <typename T>
		TStrong<T> instantiate() const { return instantiate(); }
		virtual Node& call(const Message& msg);

		String _name;
		Array _shares;
		Array _deps;
		//	Trait가 Node다. 즉, Statement도, Class도 올 수 있다.
		//	_members는 _shares + _deps 로 구성된다.
	};
	template <typename T>
	class TInterfaceClass : public Type {
		virtual Object instantiate() const {
			//ERROR
			return Null();
		}
	};
	template <typename T>
	class TConcreteClass : public Type {
		virtual Object instantiate() const {
		}
	};
	//	Native 클래스들을 World에 visible하게 만들어주는 클래스.
	//	T::ClassSpecifier가 TConcrete혹은 TIneterface를 가리킨다.
	//  TClasser 자체는 World에 visible 하지 않다
	// 	모든 템플릿들은 World에 visible 하지 않다.
	template <typename T>
	class TClass : public T::ClassSpecifier {
	};
	class Method : public Type {
		virtual Result& execute();
	};
	class WorldMethod : public Method {
		Block _block;
	};
	class Statement : public Type {
		virtual Result& execute() = 0;
	};
	class Intendation : public Statement {
		Message _msg;
		TWeak<Method> _method;
		// _this 포인터가 Node다. 이 Node에는 Statement, Method도 다 포함된다는 것이다.
		TWeak<Object> _this; 
	};
	class Block : public Statement {
		TArray<Statement> _stmts;
	};
	/////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////






	//	기본 타입:	-----------------------------------------------	
	//	객체, C++의 인스턴스를 말한다. 시스템에 여러개가 생길 수 있다.
	class Variable : public Node {
	};
	//	이름이 인스턴스마다 다르다
	class NamedVariable : public Variable {
		String _name;
		virtual const String& getName() { return _name; }
	};
	//	자기만의 member를 가질 수 있다.
	class Object : public NamedVariable {
		Class _cls;
		virtual Container& getMembers() { return _members; }
        Object(Class& klass) {
            _class = klass;
            _variables = klass.getVariables();
            _members.chain(klass.getMethods());
            _members.chain(_variables);
        }
	    Members& getVariables() { return _member.getControl()[1]; }

		//	Member는 Class.members로부터 복사된다. _methods(share) + _variables(copy)
		Chain _members;
	};
	//	primitive 타입들은 속도가 중요하다. 최적화가 필요하다. Object로 해버리면 매번 members가 생성될 것이다.
	class Primitive : public Variable {
		virtual const String& getName() const {
			static String inner;
			return inner;
		}
	};
	class Number : public Primitive {
	};
	class Integer : public Number {
	};
	class Float : public Number {
	};
	class Result : public Primitive {
		void log() { store(LogManager::get()); }
		void log(const String& fmt, ...) {
			_inflated.release();
			do somthing with vsnprintf to _inflated.

			log();
		}
		This& operator()() { dump(); return *this; }
		This& operator()(const String& fmt, ...);
		const String& getMessage() const {
			if(_inflated.size() > 0)
				return _inflated;

			return _onMessage();
		}
		virtual const String& _onMessage() = 0;
		virtual InstanceVisitor& visitor(InstanceVisitor& visitor) const {
			return visitor.store("message", getMessage().to<const char*>());
		}
		static String _inflated;	
	};
	class Char : public Primitive {
	};
	class Null : public Primitive {
	};
	class Void : public Primitive {
	};
	// String은 밖에서 봤을때는 TCell<Char> 처럼 보여야한다.
	// 하지만 퍼포먼스 때문에 실제로는 char에대한 배열이여야 한다.
	// Container는 껍데기만 있다. 속을 wstring의 delegation으로 채운다.
	class String : public Container, private std::wstring {
	};
	class Members : public Array {
	};
	class Arguments : public Members {
	};
	//	Object를 바인딩하고 있으며 World에서는 Object와 분간이 가지 않는다. 즉, Reference의 T<클래스>는 없어야 한다. Object처럼 동작해야 한다.
	//	TString의 delegation한다.
	//	Bind와 Reference를 한데 묶을 수 없다(배열 같은 곳에) 하지만 World 코드 위에서 Bind를 사용하는 경우는 없을 것이다.
	class Reference : public NamedVariable {
		Reference();
		Reference(const Class& cls) : Super(cls) {}
		Object& get();
		wbool isBinded() const;

		virtual Container& getMembers() { return _obj->getMembers(); }
		TStrong<Object> _obj;
	};
	//	T는 Object보다 하위여야 한다.
	template <typename T>
	class TReference : public Reference {
		TReference() : Reference(TClass<T>()) {}
		//	virtual이 아니기에 hiding 되므로 에러가 아니다.
		T& get();
	};
    class Node : public Instance {
		virtual String& getName() = 0;	
		virtual Node& call(const Message& msg)
		wbool isCallable(const Message& msg);
        virtual Container& getMembers() {
			//	기본적으로 Class의 Member를 반환한다. 이렇게 하면 Node는 자신만의 변수를 갖지 못한다. 
			return getClass().getMembers();
		}
		virtual Strong to(const Class& cls);
		virtual const String& getName() const = 0;
		virtual Result& setName(const String& newname) = 0;
    };







	==================================================
    //  Object는 World의 객체다. 객체는 항상 객체라는 타입이다. A라는 클래스의 객체와 B라는 클래스의 객체는 Native적으로,
    //  동일한 클래스의 객체다. 바로 이부분이 헷갈리기 쉬운 부분이며 동시에 World의 재사용성을 높여주는 부분이기도 하다.

	//	RETURN_T=String& is by-ref and sharable.
	/* So, Above macro will expand like this,
	 *
	 * RET_T = "String&"
	 * NAME = "addString"
	 * __VA_ARGS__ = rest of arguments.
	 *
	 * class addStringMethod : public Method {
	 * 		W_DECL_CLASS(addStringMethod, Method)
	 *
	 * 		typedef Mashall<RET_T>::MashalledType ReturnType;
	 * 		ReturnType _return;
	 * 
	 * public:
	 *		addStringMethod() 
	 *			// Mashall<RET_T>::RefindType is String
	 *			// Mashall<RET_T>::MashalledType is Reference<String>
	 *			// Mashall<RET_T>::isReference is 1
	 *			// Mashall<RET_T>::isSharable is 1
	 *
	 * 			// Occupiable = Reference<Occupiable> 은, rhs의 Sharable의 값이 Occupiable로 들어간다
	 *			// 이는 Occupiable은 어떻게 해서라도 값vs값의 할당이 일어나야 하기 때문이다.
	 *			// 물론 Reference<Occupiable> = Occupiable의 경우에는 Reference::operator=()가 된다.
	 *			// 그래서 아래의 경우에는 원본이 Bind로 라이프사이클이 관리되고, 그것이 Sharable이든
	 *			// Occupiable이든 값은 return으로 들어갈 수 있다.
	 *			_return = Reference(Mashall<RET_T>::RefindType());
	 *
	 *			_arguments << Reference<MyFirstWorldModule>() // thisptr
	 *			
	 *			char* __VA_ARGS_를 split하고, loop를 돌면서 적합한 TClass<T>를 만들어서 arguments
	 *			에 넣어야 한다. 이 것을 하는 도중에 T* arg,  T  *  args,  T  *args 같은 케이스들도
	 *			문제없이 파싱할 수 있어야 한다.
	 *
	 *			어떻게?
	 *
	 *
	 *			_fptr = &MyFirstWorldModule::addString;
	 *
	 *		}
	 *
	 *		String& (addStringMethod::*_fptr)(String&, __VA_ARGS_...);
	 *
	 * 		//	World에서 메소드를 실행하기 위한 가장 짦은 인터페이스이다.
	 *		//	Native를 위한 인자의 가공이 시작된다.
	 *		virtual Bind<Node> call(const Arguments& args) {
	 *			if(Mashall<RET_T>::sharable)
	 *				if(is_ref) // is_ref에는 Reference로 반환한경우도 포함이 되어야 한다.
	 *					return _return = (me->*_fptr)(args[0].to<String>(), args[1].to.... 재귀 );
	 *				else
	 *					//	RET_T는 Sharable인데, 값으로 반환한 경우다. 불가피하게 퍼포먼스가 소모.
	 *					return _return = (me->*_fptr)(args[0].to<String>(), args[1].to.... 재귀 ).clone();
	 *		}
	 * };
	 */
	#define WRD_DECL_2(T, S)	.......
	#define WRD_DECL_3(T, S, M)	\
		WRD_DECL_2(T,S)	\
	protected:	\
		static const Result& _onInitializeMethods(List<Method>& tray) {	\
			FOR_EACH()
		}

	//	사용법1:
	//		.HPP에서
	class MyFirstWorldModule : public Object {
		WRD_DECL_ONLY(MyFirstWorldModule, Object, 
			String, addString, (String&, String&)
			//	조건1. ,로 구분한다.
			//	조건2. 인자명 없다.
		) // static onInitializeMethods() 구현된다.
			//	조건3. 시작과 끝 ()를 넣는다.

	public:
		String addString(String& arg1, String& arg2) {
			//	Reference의 사용방법1 : 
			Reference<String> ret = new String(arg1 + arg2);
			//	방법2:
			Reference<String> ret = arg1.clone();
			*ret += arg2;
			//	방법3:
			Reference<String> ret = (arg1 + arg2).clone();
			//	방법4:
			Reference<String> ret = String::make();
			*ret = arg1 + arg2;
			
			return ret;
		}
	};
	//	.CPP 구현 없음.

	//	사용법2:
	//	.HPP에서
	class MyFirstWorldModule : public Object {
		WRD_DECL(MyFirstWorldModule, Object) // static onInitializeMethods(); 선언 된다.

	public:
		String addString(String& arg1, String& arg2); // 여기서 정의해도 상관없다.
	};
	//	.CPP에서
	WRD_DEF(MyFirstWorldModule, 
		(String, addString, String&, String & const) // static onInitializeMethods() 구현들어간다.
	)
	String MyFirstWorldModule::addString(String& arg1, String & const arg2) {
		... dosomething ...
	}
}
