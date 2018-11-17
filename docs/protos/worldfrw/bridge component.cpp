//	Visibility Macro:
//		let natives be visible to World managed area.
//
//	Usage:
//		class A {
//			WRD_CLASS(A, (
//				CTOR(),
//				CTOR(int),
//				API(void, print, (int, float, char*)),
//			))
//		public:
//			A();
//			A(int a);
//
//			void print(int a, float b, char* c)
//			void foo();
//			static int foo1();
//			int foo1(char);
//			void foo1(float) const;
//			void foo1(float);
//		};

class FuncChecker {
public:
    enum FunctionType {
        NONE = 0,
        NON_MEMBER_FUNCTION = 1,
        MEMBER_FUNCTION = 10,
        CONST_MEMBER_FUNCTION = 100,
    };

    virtual int getTypeValue() const = 0;
    bool isConst() const { return getTypeValue() & CONST_MEMBER_FUNCTION; }
    bool isMember() const { return getTypeValue() & MEMBER_FUNCTION; }
	bool isNonMember() const { return getTypeValue() & NON_MEMBER_FUNCTION; }
    bool isExist() const { return getTypeValue(); }
};
//	FuncChecker creation macro:
//		usage:
//			WRD_CREATE_FUNC_CHECKER(printChecker, print)
//			typedef printChecker<void, A, int, float, char*> printC;
//			printC::isConst() == false
//			printC::isMember() == true
//			printC::isNonMember() == false
//			printC::isExist() == true
//
//			WRD_CREATE_FUNC_CHECKER(foo1Checker, print)
//			typedef foo1Checker<int, A> foo1Checker;
//			foo1Checker::isConst() == false
//			foo1Checker::isMember() == false
//			foo1Checker::isNonMember() == true
#define WRD_CREATE_FUNC_CHECKER_FOR_CTOR(...) 
#define _FUNC_CHECKER_NAME(NAME) NAME##Checker___
#define WRD_CREATE_FUNC_CHECKER_FOR_API(NAME, FUNC_NAME) \
    template<typename R, typename V, typename ... Args>    \
    class _FUNC_CHECKER_NAME(NAME) : public FuncChecker\
    {    \
        R (V::*FPTR)(Args...);    \
        R (V::*FCPTR)(Args...) const;    \
        R (*FFPTR)(Args...);    \
        template<typename C> static constexpr auto _foo1(int) -> decltype(FFPTR = &C::FUNC_NAME, int{}) { return FuncChecker::NON_MEMBER_FUNCTION; }    \
        template<typename> static constexpr auto _foo1(...) { return NONE; }    \
        template<typename C> static constexpr auto _foo2(int) -> decltype(FPTR = &C::FUNC_NAME, int{}) { return FuncChecker::MEMBER_FUNCTION; }    \
        template<typename> static constexpr auto _foo2(...) { return NONE; }    \
        template<typename C> static constexpr auto _foo3(int) -> decltype(FCPTR = &C::FUNC_NAME, int{}) { return FuncChecker::CONST_MEMBER_FUNCTION; }    \
        template<typename> static constexpr auto _foo3(...) { return NONE; }\
    \
    public:    \
        virtual int getTypeValue() const {    \
            static constexpr int value = _foo1<V>(int{}) + _foo2<V>(int{}) + _foo3<V>(int{});    \
            return value;    \
        }\
    };

#define WRD_CLASS_1(THIS)	\
	WRD_CLASS_3(THIS, Adam, ())
#define WRD_CLASS_2(THIS, MEMBERS)	\
	WRD_CLASS_3(THIS, Adam, MEMBERS)

#define _CLASS_TEMPLATE(E) WRD_CREATE_FUNC_CHECKER_FOR_##E
#define _REFLECT(E)	WRD_##E

#define WRD_CLASS_3(THIS, SUPER, MEMBERS)	\
private:	\
	WRD_EACH(_CLASS_TEMPLATE, MEMBERS)	\
public:	\
	typedef THIS This;	\
	typedef SUPER Super;	\
	static TClass<This> reflect(TClass<This>& init)	\
	{	\
		Container& mems = init.getMembers();	\
		WRD_EACH(_REFLECT, MEMBERS)	\
	}

#define WRD_CTOR(...)	\
	mems += TNativeCtor<This, __VA_ARGS__>();
#define WRD_API(RET, NAME, ARGS)	\
	{	\
		static NAME##Checker___<RET, This, WRD_UNWRAP ARGS> NAME##_checker___;	\
		mems += TNativeMethoder<RET, This, WRD_UNWRAP ARGS>(NAME##_checker___, &This::NAME);	\
	}
//	C++17이 적용되면 inline이 가능하므로 위처럼 memps를 만들지않고 static 클래스가 시작과 동시에 인스턴스를 만들어서 
//	지정한 Class 밑으로 들어가게 하면 된다.

template <typename T>
class TBlackbox : public Object {
//  일시적으로 NativeType들(주로 pointer나 객체) World로 끌고 들어오게 한다. 그러나 이는 World개발자에게는 어떠한 인터페이스도 노출시키지 않는다. 분명 존재하며, Native(=모듈) 간에는 인터렉션이 발생하지만 World개발자에게는 블랙박스로만 보이게 되는 것들을 말한다. 기존 Native 개발에서 비슷한 것을 찾아본다면 "핸들" 이 여기에 해당할 것이다.
    static_assert(T is not sub of Thing)
    TBlackBox(T& origin) : _bean(&origin) {}
    T& get() { return *_bean; }
    const T& get() const { return *_bean; }
    T* _bean;
};
template <typename T>
class TBlackBox<T*> : public Object {
	//  void*도 호환된다.World개발자도 이걸 정의할순 없어도, 모듈로부터 받아서 가지고는 있어야 하기 때문에 Object로 삼는 것이다.
    static_assert(T is not sub of Thing)
    A(T* origin) : _bean(&origin) {}
    T* get() { return *_bean; }
    //	World는 포인터를 사용하지 않으나, 이것 어쩔 수 없다. 
    const T* get() const { return *_bean; }
    T** _bean;
}

//	Lambda method is just a ManagedMethod nested and assigned by Delegator.
template <typename T, typename... ArgTypes>
class TNativeCaller: public Method {
	virtual Refer _callNative(ArgTypes... args) = 0;

	Result& _validateArgs(ArgTypes&... args) {
        void* tray[] = {&args...};
        for(int n=0; n < sizeof...(args) ;n++)
            if( ! tray[n])
                return InvalidData;
        return Success;
    }

	template <size_t... n>
	Object* _castEach(const Args& args, index_sequence<n...>) {
		return _callNative((args[n].toImplicitly<Args>()->down<ArgTypes>())...);
	}
	Object* _serialize(const Args& args) {
		return _castEach(args, index_sequence_for<ArgTypes...>{});
	}
	Node& _getThis() {
		if(isStatic())
			return NULL;
		return args[args.size()-1];
	}
	virtual Refer _onRun(Msg& msg) {
		if(Super::_onRun(msg))
			return SuperFail.err();

		return _serialize(msg.getArgs());
	}
};

template <typename T, typename... ArgTypes>
class TNativeCtor: public TNativeCaller<T, ArgTypes...> {
	virtual Refer _callNative(T* thisptr, ArgTypes... args) {
        if(_validateArgs(args...))
            return Refer();
        return new T(args...);
    }
	virtual bool isConst() const { return true; }
	virtual bool isStatic() const { return true; }
};

template <typename Ret, typename T, typename... ArgTypes>
class TNativeMethoder : public TNativeCaller<T, ArgTypes...> {
	typedef Ret (T::*Fptr)(ArgTypes...);
	typedef T Class;
	Fptr _fptr;

	TNativeMethoder(const FuncChecker& checker, Fptr fptr) : Super(), _checker(checker), _fptr(fptr) {}

	//	TODO: static 메소드의 구현. (Method에 static여부가 있어야 할 것 같다.
	//	TODO: CtorWrapper를 static 메소드 화.

	virtual Refer _callNative(T* thisptr, ArgTypes... args) 
		if(_validateArgs(args...))
            return Refer();
		if(isConst())
		{
			const T& thisptr = _getThis().down<const T>();
			if(thisptr.isNull())
				return Refer();
			return Refer((thisptr.*_fptr)(args...) );
		}

		T& thisptr = _getThis().down<T>();
		if(thisptr.isNull())
			return Refer();
        return Refer( (thisptr.*_fptr)(args...) );
	}

	virtual bool isStatic() const {	return _checker.isNonMember(); }
	virtual bool isConst() const { return _checker.isConst(); }
	const FuncChecker& _checker;
};

template <typename Ret, typename T, typename... ArgTypes>
class TNativeMethoder<Ret, T, ArgTypes...> : public TNativeMethod<T> {
	typedef Ret (T::*Fptr)(ArgTypes...);
	Fptr _fptr;

	TNativeMethoder(Fptr fptr) : Super(), _fptr(fptr) {}

	//	TODO: static 메소드의 구현. (Method에 static여부가 있어야 할 것 같다.
	//	TODO: CtorWrapper를 static 메소드 화.

	virtual Refer _callNative(ArgTypes... args) 
		if(_validateArgs(args...))
            return Refer();
        return Refer( _fptr(args...) );
	}
	virtual bool isStatic() const { return true; }
};
