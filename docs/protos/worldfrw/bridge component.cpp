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
    World는 포인터를 사용하지 않으나, 이것 어쩔 수 없다. 
    const T* get() const { return *_bean; }
    T** _bean;
}



//	검증용 코드. 차후에 삭제 예정.
#include <iostream>
#include <typeinfo>
#include <type_traits>
#include <cxxabi.h>

using namespace std;

template <typename T, typename F>
class Is {
public:
	typedef short yes;
	typedef char no;

	static yes _sfinae(void(T::*fmptr)());
	static no _sfinae(...);
	enum {
		VALUE = sizeof(_sfinae((F) 0)) == sizeof(yes)
	};
};

template <typename A, typename ...Args>
class Is1 {
public:
	static bool equal(char const * a, char const * b) {
		if(*a == '(') {
			return true;
		}
		return *a == *b && (*a == '\0' || equal(a + 1, b + 1));
	}
	static bool is_constructor(const char* src) {
		int status = 0;
		char *name = abi::__cxa_demangle(typeid(A).name(), 0, 0, &status);
		if( ! equal(src, name)) {
			return false;
		}
		return is_constructible<A, Args...>::value;
	}
};

class My : public Object {
	WRD_CLASS(My, Object,
		WRD_VISIBLE(void, print),
		WRD_VISIBLE(void, print, int),
		//	class My_void_print_int : public TNativeMethod<void/*반환*/, int/*...Args*/> {
		//		요구사항1. owner가 My라는걸 런타임에는 알 수있어야 함.
		//			고찰을 통해, 컴파일 타임에 하는 것은 
		//			함수이름을 가져오는 문제로 인하여, 도저히 불가능하다는 걸 알았다.
		//		요구사항2. 함수이름을 매크로로 생성해 줘야함.
		//		virtual const String& getName() const { 
		//			static String inner = #print;
		//			return inner;
		//		}
		//		요구사항3. 마샬링이 일어나야 한다.
		//		요구사항4. 생성자인지 여부를 런타임에 판단해야 하며, 한번 판단하면 캐시를 생성하여,
		//			다음부터는 판단하지 않도록 한다. 생성자여부는 다음으로 판단한다.
		//			1. getClass().getName() == getName() 이며,
		//			2. is_constructible<Args...>::value가 true가 나옴으로써, 아무인자나 대충 써낸것이
		//			아닌지를 판단해야한다. 이 값도 외부에 공개해야 한다.
		//		wbool isConstructor() const {
		//			...
		//		}
		//		요구사항5. TNativeMethod는 마샬링, 함수포인터 소유, run함수 구현등을 담당한다.
		//			쉽게보면 bridge컴포넌트의 벡엔드다. 매트로는 프론트엔드고.
		//		요구사항6. 매크로를 더 C 함수선언 스타일로 작성하게 하는 방법은 없을까?
		//	};
		WRD_VISIBLE(void, print, int, float, char*)
		// 주어진 print가 static인지, const인지는 sfinae로 알 수 있음.
	)
	void print()
	static void print(int a);
	void print(int a, float b, char* c) const;
};
