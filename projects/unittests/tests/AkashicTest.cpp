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

    //    basic:
    A a;
    {
        const Block& blk = a.getBlock();
        T(blk.isExist())
        T(blk.getSerial())
        const Chunk& chk = blk.getChunk();
        T( ! chk.isExist())
    }

    return "";
WRD_TEST_END(AkashicTest)
