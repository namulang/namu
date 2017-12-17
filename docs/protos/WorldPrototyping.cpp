namespace wrd
{
	//	typedef들:--------------------------------------------
	typedef int wid;
	typedef int wint;
	typedef bool wbool;
	typedef int wcount;
	class Result;
	template <typename S, typename T> class Bind;
	class Strong;
	class Weak;
	class Node;
	class Object;


	class Thing {
    public:
        virtual Result& release() = 0;
		virtual Bind<Strong, Thing> clone() = 0;
		//dump?
    };
	class Instance : public Thing { // Instance 관리가 가능함.
		//	w로 시작하는 작은 타입def는 primitive에 대한 typedef를 의미한다. 객체가 아니다.
		wid getId() const;
		wid _id;
	};

	//	Bind 컴포넌트:----------------------------------------
	class Weak : public Instance {
		Node& get();
		virtual Result& bind(const Node& trg);
		wbool isBinded() const;
	};
	class Strong : public Weak {
		virtual Result& bind(const Node& trg);
	};
	//	Prefix T는 템플릿을 의미한다.
	template <typename S, typename T>
	class TBind : public S {
		//	Weak::get이 virtual이 아니기때문에 여기서 메소드은폐가 된다. 그래서 중복에러가 나지 않는다.
		T& get();
	};
	//	편의용 템플릿. c++11의 alias declaration 를 사용한다.
	template <typename T>
	using TWeak = TBind<Weak, T>;
	template <typename T>
	using TStrong = TBind<Strong, T>;



	//	Container컴포넌트:------------------------------------------
	//		Container는 주의할것이, C++을 위한 것이 아니라 월드를 위한 Conatiner이라는 점이다. 그래서 기본타입이 무조건 Node이다.
	class Iterator : public Object {
	};
	class Container : public Object, public Containable {
		virtual Result& insert(const Iterator& pos, const Node& trg) = 0;
		virtual Result& remove(const Iterator& pos, const Node& trg) = 0;
		virtual Node& _get(const Iterator& pos) = 0;
		wcount getLength() const { return _length; }
		Node& get(const Iterator& pos) { return _get(pos); }
		virtual Iterator& getIterator() = 0;
		const Iterator& getIterator() const;
		Result& each(const Method& lambda);
		template <typename T>
		Result& each(T lambda);
		// 삽입가능한 타입을 말한다.
		// 생성시 한번 정해지면 변경이 불가능해야 한다.
		virtual Class& getTrait() { return TClass<Node>(); }

	protected:
		wcount _length;
	};
	class SolidContainer : public Container {
		wcount getSize() const { return _size; }
		virtual wcount resize(wcount newsize) = 0;

	protected:
		wcount _size;
	};
	class Array : public SolidContainer {
		class ArrayIterator : public Iterator {
		};
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



	//	MetaClass 컴포넌트	---------------------------------------
	class Type : public Object {
	};
	typedef TArray<Class> Classes;
	class Class : public Type {
		virtual const String& getName() const { return _name; }
		virtual const Classes& getSupers() const;
		virtual const Classes& getSubs() const;
		//	Shared Members: 모든 객체마다 share하는 클래스의 멤버들. 공유변수 및 Method가 여기에 속한다
		const Members& getShares() const { return _shares; }
		//	(Object) Dependent Members: 객체에 종속되는 멤버들. 객체마다 서로 다른 값을 갖는 멤버들로, 멤버변수가 여기에 속한다.
		const Members& getDependents() const { return _deps; }
		virtual Object instantiate() const = 0;
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
	class InlineStatement : public Statement {
		Message _msg;
		Weak<Method> _method;
		// _this 포인터가 Node다. 이 Node에는 Statement, Method도 다 포함된다는 것이다.
		Weak<Object> _this; 
	};
	class Block : public Statement {
		Array<Statement> _stmts;
	};



	//	기본 타입:	-----------------------------------------------	
	//	객체, C++의 인스턴스를 말한다. 시스템에 여러개가 생길 수 있다.
	class Variable : public Node {
	};
	//	이름이 있다.
	class NamedVariable : public Variable {
		virtual String& getName() = 0;	
		String _name;
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
	//	World에 visible 하지 않으며(Node가 아님), Instance 관리도 필요없다(Instance가 아님).
	class Message : public Thing {
		String _name;
		Arguments _arguments;
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
    public:
		virtual Node& call(const Message& msg)
        virtual Container& getMembers() {
			//	기본적으로 Class의 Member를 반환한다. 이렇게 하면 Node는 자신만의 변수를 갖지 못한다. 
			return getClass().getMembers();
		}
		virtual Strong to(const Class& cls);
		virtual const String& getName() const = 0;
		virtual Result& setName(const String& newname) = 0;
    };


	
	class 







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
