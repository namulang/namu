#include <type_traits> // over c++11

typedef bool wbool;
typedef int wint;
typedef char wchar;
typedef wchat_t wwchar;
typedef float wfloat;
typedef wint wcount;
typedef wint windex;

template <typename T>
class Nuller {
	T* ptr = 0;
	T& ref = (T&) *ptr;
};

#define WRD_CHK_THISPTR(TYPE)	\
	if(isNull())	\
		return Nuller<TYPE>::ref;
//	World는 객체 안에서 다른 객체에 접근하는 접근자함수들에 경우에는 DelayingNullCorruption으로 인해 객체가 Null이라고 해도 Null을 반환할뿐 프로그램이 죽지는 않는다.
//	접근자 아닌 경우에는 "속도문제" 로 인해 수행하지 않는다.
//	또한 반환형이 객체에 대한 레퍼런스나 포인터가 아닌경우에도 정상적인 반환값과 겹칠 수있기 때문에 체크하지 않는다.

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
	typedef typename std::conditional<IS_ADT, ConcreteClass<T>, InterfaceClass<T>>::type TypeClass;
};

template <typename T>
class TTemplateChecker : public Checker {
	template <template<typename> class Template, typename X>
	static yes _foo(Template<X>*);
	static no _foo(...);

public:
	static const wbool IS = sizeof(_foo((T*)0)) == sizeof(yes);
};
