#include "Thing.hpp"
#include "../memory/TStrong.hpp"

namespace wrd
{
#define THIS Thing

	WRD_CLASS_DEF(Thing)

	const Class& THIS::getSuper() const { return getClass().getSuper(); }
	wbool THIS::isNull() const { return !this; }
	wbool THIS::isExist() const { return this; }
	wbool THIS::isSuper(const Class& it) const { return getClass().isSuper(it); }
	wbool THIS::isSuper(const Thing& it) const { return getClass().isSuper(it.getClass()); }
	template <typename T> wbool THIS::isSuper() const { return getClass().isSuper(T::getStaticClass()); }
	wbool THIS::isSub(const Thing& it) const { return it.getClass().isSuper(getClass()); }
	wbool THIS::isSub(const Class& it) const { return it.isSuper(getClass()); }
	template <typename T> wbool THIS::isSub() const { return T::getStaticClass().isSuper(getClass()); }
	//	to는 명시적캐스팅이다. 
	//		사용자의 개입이 가능한 유일한 캐스팅의 1 종류이며, 
	//		A타입에 대한 명시적캐스팅은 어떠한 타입이 나올지 제한되지 않는다.
	//		A클래스.to()는 전혀다른 B객체가 나올 수도 있다.
	Strong THIS::to(const Class& cls) { return Strong(); }
	CStrong THIS::to(const Class& cls) const
	{
		WRD_UNCONST()
		return unconst.to(cls);
	}
	//	Casting:
	//		World의 캐스팅은 다음으로 구분된다.
	//			1) native 다운캐스팅:	thing::down<T>(), Thing::down(Class&)
	//			[invisible]	native에서 편의를 위해 제공되는 함수다.
	//
	//			2) 명시적캐스팅:	Thing::to(Class&), Thing::to<T>()
	//			[visible] 명시적 캐스팅은 총 3가지로 이루어져있다.
	//				1. 다운/업캐스팅(Thing::down(Class&)를 사용한다)
	//				2. 묵시적 캐스팅 파이프
	//				3. 생성자를 통한 캐스팅: cls가 가지고 있는 생성자를 통해서,
	//				변환이 가능한지 확인하고, 가능하다면 이걸 이용한다.
	//				속도가 매우 오래걸린다.
	//
	//			3) 묵시적캐스팅:	2번과 동일
	//			[invisible, automatically] 명시적 캐스팅은 속도를 많이 필요로 하기,
	//			때문에 매 함수 호출시 인자마다 호출될 캐스팅으로는 적합하지 않다.
	//			묵시적 캐스팅은 pretype에 대해서 빠르게 동작하는 캐스팅을 의미하며,
	//			사용자가 캐스팅하는 주체가 pretype일 경우에 한해서 자동으로 묵시적
	//			캐스팅이 이루어진다.
	//				예)	void print(int a)
	//				MyClass cls;
	//				print(cls); // err. MyClass -> int는 묵시적캐스팅이 아니다.
	//				print(3.5); // ok. float은 pretype이므로 묵시적 캐스팅이 동작한다.
	//			묵시적 캐스팅은 각 pretype들이 to함수를 override해서 자신의 간이 캐스팅
	//			테이블을 끼워놓음으로써 해결한다. 중간에 msg를 만들어 보낼 필요가 없으므로
	//			속도가 더 빨라진다.

	//	구체클래스로 캐스트한다. dynamic_cast와 동급이다.
	//	invisible이다.
	Thing& THIS::_down(const Class& cls)
	{
		WRD_IS_THIS(Thing)

		if(isSub(cls))
			return *this;
		return nulr<Thing>();
	}
	const Thing& THIS::_down(const Class& cls) const
	{
		WRD_UNCONST()
		return unconst._down(cls);
	}
	//	가상할당자이다. 할당연산자는 virtual이 안되기 때문에 제대로 할당을 하고 싶다면 항상 구체타입을 알고 있어야만 한다.
	Res& THIS::assign(const Thing& it)
	{
		WRD_IS_NULL(it)
		//	TODO:
		return wasgood;
	}
	//	Visitor에 의해서 하위 구성요소(ownee)들을 어떻게 순회시킬지를 정한다.
	Res& THIS::_tour(Visitor& visitor) const { return wasgood; }
	Res& THIS::_tour(Visitor& visitor)
	{
		WRD_UNCONST()
		return unconst._tour(visitor);
	}
}
