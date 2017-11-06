namespace W
{
    template <typename T>
    class Bind : public Thing {
    public:
    };
    class Result : public Thing {

    };
    class Thing {
    public:
        virtual const Result& release();
        virtual Bind<Thing> clone() = 0;
    };
    class Container : public Thing {
    public:
    };
    template <typename T>
    class Array : public Container {

    };
    class Members : public Array<Node> {
    public:
        
    };
    class Node : public Thing {
    public:
        virtual Bind<Node> call(const String& msg, Array<Argument> args) {
            
        }
        virtual Members& getMembers() = 0;
    };
	class Message : public Thing {
	};
    class Method : public Node {
    public:
        virtual Bind<Node>& call(const Message& msg) {
        }
		virtual Node& call(const Arguments& args) = 0;
    };
    class Class : public Node {
    public:
        virtual const String& getName() const = 0;
        virtual const Array<Class>& getSupers() const = 0;
        virtual const Array<Class>& getSubs() const = 0;
        virtual Members& getMembers() { return _members; }
        Members& getMethods() { return _methods; }
        Members& getVariables() { return _variables; }
        Object incarnate() const {// World 객체를 만드는 것이다.
            return Object(*this);
        }

        virtual Bind<Node> call(const String& msg, Array<Argument> args) {

        }
        //  Class의 각 _variables는 부모의 _variables를 clone() 한 뒤, 자기만의 심볼을 뒤에 push 한 것이다.
        //          " _methods 동일. _members는 자연스럽게 이게 된 상태.
        //  ! 논리적으로 _members 안에는 중복 이름이 있어서는 안된다.

        
        Members _variables;
        Members _methods;
        Chain<Node> _members;
    };
    template <typename T>
    class Classer : public Class {
        //  TClasser는 World에 visible 하지 않다:
        //      visible하다는 것은 논리적으로는 "World에서 접근 가능함" 이라는 뜻이며, 
        //      물리적으로는 "파싱테이블에 매핑되어있어서 Txt가 적절한 객체로 생성될 수 있음" 이라는 뜻이다.
        //      C++안에서만 Classer<T>를 사용할 수 있다.
    public:
    };
    class WorldClass : public Class {
    public:
    };      

    //  Object는 World의 객체다. 객체는 항상 객체라는 타입이다. A라는 클래스의 객체와 B라는 클래스의 객체는 Native적으로,
    //  동일한 클래스의 객체다. 바로 이부분이 헷갈리기 쉬운 부분이며 동시에 World의 재사용성을 높여주는 부분이기도 하다.
    class Object : public Node {
    public:
        Object(Class& klass) {
            _class = klass;
            _variables = klass.getVariables();
            _members.chain(klass.getMethods());
            _members.chain(_variables);
        }

    Members& getMembers() { return _members; }
    Members& getVariables() { return _variables; }

    private:
        Weak<Class> _class; // 이게 뭘 가리키느냐에 따라서, 어떠한 World 객체인가가 결정되는 것이다.
        Members _variables;
        Chain<Node> _members;
    };


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
