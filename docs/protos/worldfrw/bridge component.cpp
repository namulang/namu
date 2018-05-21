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
//			void print(int a, float b, char* c);
//		};
#define WRD_CLASS_1(THIS)	\
	WRD_CLASS_3(THIS, Adam, ())
#define WRD_CLASS_2(THIS, MEMBERS)	\
	WRD_CLASS_3(THIS, Adam, MEMBERS)
#define WRD_CLASS_3(THIS, SUPER, MEMBERS)	\
public:	\
	typedef THIS This;	\
	typedef SUPER Super;	\
	static TClass<This> reflect(TClass<This>& init)	\
	{	\
		Container& mems = init.getMembers();	\
		WRD_EACH(_REFLECT, MEMBERS)	\
	}
#define _REFLECT(E)	\
	WRD_##E

#define WRD_CTOR(...)	\
	mems += TCtorWrapper<This, __VA_ARGS__>();
#define WRD_API(RET, NAME, ARGS)	\
	mems += TMethodWrapper<This, &This::Name, WRD_UNWRAP ARGS>();
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
    World는 포인터를 사용하지 않으나, 이것 어쩔 수 없다. 
    const T* get() const { return *_bean; }
    T** _bean;
}

