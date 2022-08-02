#include "../../common/dep.hpp"

using namespace namu;

TEST(macroTest, nul) {

    wint a = 5;
    wint* aPtr = &a;
    wint* aNul = nullptr;
    wint& refNul = nulOf<wint>();
    wint& refA = *aPtr;

    ASSERT_TRUE(nul(refNul));
    ASSERT_FALSE(nul(refA));
    wbool isNul = nul(aNul);
    ASSERT_TRUE((void*) isNul);
    ASSERT_FALSE(nul(aPtr));
}

TEST(macroTest, WRD_GETtest) {
    struct A {};
    struct B {
        A& getA() {
            return a;
        }
        A& getNul() {
            return nulOf<A>();
        }
        A a;
    } b;
    struct C {
        B& getB() {
            return b;
        }
        B& getNul() {
            return nulOf<B>();
        }
        B b;
    } c;
    struct D {
        C& getC() {
            return c;
        }
        C& getNul() {
            return nulOf<C>();
        }
        C c;
    } d;

    A& a = WRD_GETS(b, getA());
    ASSERT_FALSE(nul(a));
    A* aNul = &WRD_GETS(b, getNul());
    ASSERT_TRUE(nul(aNul));

    A& a0 = WRD_GETS(b.getNul());
    ASSERT_TRUE(nul(a0));

    A& a2 = WRD_GETS(c,getB(),getA());
    ASSERT_FALSE(nul(a2));
    A* a2Nul = &WRD_GETS(c,getNul(),getA());
    ASSERT_TRUE(nul(a2Nul));

    A& a3 = WRD_GETS(d,getC(),getB(),getA());
    ASSERT_FALSE(nul(a3));
    A* a3Nul = &WRD_GETS(d,getNul(),getB(),getA());
    ASSERT_TRUE(nul(a3Nul));

    A& a4 = WRD_GETS(d.getC().getB(),getA());
    ASSERT_FALSE(nul(a4));
    A* a4Nul = &WRD_GETS(d.getC().getB(),getNul());
    ASSERT_TRUE(nul(a4Nul));
}

TEST(macroTest, UnconstCalltest) {
    struct A {
        WRD_DECL_ME(A)

    public:
        wbool foo() {
            return true;
        }
        wbool foo() const WRD_UNCONST_FUNC(foo())
    } a;

    const A& aConst = a;
    ASSERT_TRUE(aConst.foo());
}
