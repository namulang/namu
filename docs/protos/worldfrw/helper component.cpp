#include <type_traits> // over c++11

typedef bool wbool;
typedef int wint;
typedef char wchar;
typedef wchat_t wwchar;
typedef float wfloat;
typedef wint wcount;
typedef wint windex;

template <typename T>
class TNuller {
public:
	static T null() { return T(); }
};
template <typename T>
class TNuller<T&> {
public:
	static T& null() { T* null = 0; return *null; }
};

//	World는 객체 안에서 다른 객체에 접근하는 접근자함수들에 경우에는 DelayingNullCorruption으로 인해 객체가 Null이라고 해도 Null을 반환할뿐 프로그램이 죽지는 않는다.
//	접근자 아닌 경우에는 "속도문제" 로 인해 수행하지 않는다.
//	또한 반환형이 객체에 대한 레퍼런스나 포인터가 아닌경우에도 정상적인 반환값과 겹칠 수있기 때문에 체크하지 않는다.

#define WRD_IS_NULL_2(VALUE, RET)	\
	if((VALUE.isNull())) {			\
		RET.warn(#VALUE);			\
		return RET;					\
	}
#define WRD_IS_NULL_1(VALUE)		\
	WRD_IS_NULL_2(VALUE, NullPtr)
#define WRD_IS_NULL ....

//	multiple NULL check macro:
//		if you need to check plenty arguments to be checked null
//		and return value will be same, you can accomplish it conveniently
//		with this macro.
//
//		usage:
//			WRD_IS_NULL(arg1, -1)
//			WRD_IS_NULL(arg2, -1)
//			WRD_IS_NULL(arg3, -1)
//				or
//			WRD_ARE_NULL(-1, arg1, arg2, arg3)
#define _ARE_NULL(VALUE, RET)		WRD_IS_NULL(VALUE, RET)
#define WRD_ARE_NULL(RET, ...)		NE_EACH_EXPAND(_ARE_NULL, RET, __VA_ARGS__)

#define WRD_IS_THIS_1(TYPE)			WRD_IS_NULL(*this, Nuller<Type>::ref)
#define WRD_IS_THIS_0()				WRD_IS_THIS_1(This)
#define WRD_IS_THIS ....

#define WRD_IS_CONST(RET)			\
	if((this->isConst())) {			\
		ConstCancel.warn(#RET);		\
		return RET;					\
	}

#define WRD_IS_ERR(STMT)			\
	{								\
		Result& res = (STMT);		\
		if(res)						\
			return res.err(#STMT);	\
	}
#define WRD_IS_WARN(STMT)			\
	{....

class Checker {
public:
	typedef short yes;
	typedef char no;
};

// inspired by boost::is_abstract()
template <typename T>
class TADTChecker : public Checker {
	template <typename U>
	static no _foo(U (*)());
	template <typename U>
	static yes _foo(...);

public:
	static const wbool IS = sizeof(TADTChecker<T>::template foo<T>(0)) == sizeof(yes);
};

template <typename T>
class TTemplateChecker : public Checker {
	template <template<typename> class Template, typename X>
	static yes _foo(Template<X>*);
	static no _foo(...);

public:
	static const wbool IS = sizeof(_foo((T*)0)) == sizeof(yes);
};

template <typename T, typename Super> // is T is sub of Super
class SubChecker : public Checker {
	static yes _foo(Super*);
	static no _foo(...);

public:
	enum {
		IS = sizeof(_foo((T*) 0)) == sizeof(yes)
	};
};

template <typename T>
class StaticMethodChecker : public Checker {
	template <typename R, typename... Args>
	static yes _foo( R(*)(Args...) );
	static no _foo(...);

public:
	static const bool IS = sizeof(_foo( (T) 0 )) == sizeof(yes);
};
