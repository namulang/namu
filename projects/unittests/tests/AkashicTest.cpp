#include "../TestCase.hpp"

WRD_TEST_START(AkashicTest)
    class A : public Object {
        WRD_CLASS(A, Object)
    public:
        int age;
    };
    class B : public A {
        WRD_CLASS(B, A)
    public:
        float grade;
    };

    //	basic:
    A a;
	const Block& blk = a.getBlock();
	T(blk.isExist())
	T(blk.getId().s.serial)
	const Chunk& chk = blk.getChunk();
	T( ! chk.isExist())

	std::vector<A*> arr;
	for(int n=0; n < 10; n++)
	{
		A* new1 = new A();
		const Block& blk = new1->getBlock();
		T(blk.isExist())
		T(blk.getId().s.serial > 0)
		T(blk.isBind())
		//TODO: T(blk.getBindable() == TClass<Instance>())
		//TOOD: T(blk.canBind(TClass<Instance>()))
		Id id = blk.getId();
		T(id.s.blk_n != WRD_INDEX_ERROR)
		T(id.s.chk_n != WRD_INDEX_ERROR)
		T(id.s.serial > 0)
		T(blk.isHeap())
		const Chunk& chk = blk.getChunk();
		T(chk.isExist())
		T(chk.has(*new1))
		T(chk.getEOB())
		T(chk.getHeap())
		T(chk.getLen() > 0)
		T(chk.getSize() > 0)
		new1->age = n;
		arr.push_back(new1);
    }

	for(A* e : arr)
		delete e;
	arr.clear();

    return "";
 WRD_TEST_END(AkashicTest)
