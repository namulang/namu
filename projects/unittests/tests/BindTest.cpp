#include "../TestCase.hpp"
#include <iostream>
using namespace std;

WRD_TEST_START(BindTest)
	class A : public Instance
	{	WRD_CLASS(A, Instance)
	public:
		virtual Res& release() { return wasgood; }
		virtual Strong toStrong() { return Strong(); }
		virtual Weak toWeak() { return Weak(); }
		int age;
	};
	class B : public Object
	{	WRD_CLASS(B, Object)
	public:
		B() { ++get(); }
		B(const B&) { ++get(); }
		virtual ~B() { --get(); }
		float grade;

		static wcnt& get() { static wcnt n = 0; return n; }
	};

	//	basic:
	{
		TStrong<A> b1 = new A();
		T(b1->isExist())
		T((*b1).isExist())
		const Block& blk = b1->getBlock();
		T(blk.isExist())
		T(blk.isHeap())
		Id id = blk.getId();
		T(id.s.serial > 0)
		T(id.s.blk_n >= 0)
		//TODO: Strong b2 = blk.toStrong();
		//TODO: T(b2->isNull())
		//TODO: TStrong<A> b3 = blk.toStrong();
		//TODO: T(b3->isNull())
	}

	//	nested:
	{
		T(B::get() == 0)
		B b1;
		T(B::get() == 1)
		TStrong<B> 	bb1(b1),
					bb2(b1.clone()),
					bb3;
		T(B::get() == 2)
		T(bb1.isBind())
		T(bb1->getBlock().isExist())
		T(bb1->getBlock().getStrongCnt() == 0)
		T(bb2.isBind())
		T(bb2->getBlock().isExist())
		T(bb2->getBlock().getStrongCnt() == 1)
		T( ! bb3.isBind())
		bb3 = bb2;
		T(B::get() == 2)
		T(bb3.isBind())
		T(bb3->getBlock().isExist())
		T(bb3->getBlock().getStrongCnt() == 2)
		T( ! bb2.unbind())
		T( ! bb2.isBind())
		T(bb2.get().isNull())
		T(bb3->getBlock().getStrongCnt() == 1)
		T(B::get() == 2)
		T( ! bb3.release())
		//T(B::get() == 1)
		T( ! bb1.unbind())
	}
	T(B::get() == 0)

	return "";
WRD_TEST_END(BindTest)
