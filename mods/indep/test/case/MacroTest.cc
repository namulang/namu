#include "../common/dep.hpp"

namespace wrd { namespace indep {

    TEST(MacroTest, nul) {

        wint a = 5;
        wint* aPtr = &a;
        wint* aNul = WRD_NULL;
        wint& refNul = nulr<wint>();
        wint& refA = *aPtr;

        ASSERT_TRUE(nul(refNul));
        ASSERT_FALSE(nul(refA));
        wbool isNul = nul(aNul);
        ASSERT_TRUE((void*) isNul);
        ASSERT_FALSE(nul(aPtr));
    }

    TEST(MacroTest, WRD_GETtest) {
        struct A {};
        struct B {
            A& getA() {
                return a;
            }
            A& getNul() {
                return nulr<A>();
            }
            A a;
        } b;
        struct C {
            B& getB() {
                return b;
            }
            B& getNul() {
                return nulr<B>();
            }
            B b;
        } c;
        struct D {
            C& getC() {
                return c;
            }
            C& getNul() {
                return nulr<C>();
            }
            C c;
        } d;

        A& a = WRD_GETS(b, getA());
        ASSERT_FALSE(nul(a));
        A* aNul = &WRD_GETS(b, getNul());
        ASSERT_TRUE(nul(aNul));

        A& a2 = WRD_GETS(c,getB(),getA());
        ASSERT_FALSE(nul(a2));
        A* a2Nul = &WRD_GETS(c,getNul(),getA());
        ASSERT_TRUE(nul(a2Nul));

        A& a3 = WRD_GETS(d,getC(),getB(),getA());
        ASSERT_FALSE(nul(a3));
        A* a3Nul = &WRD_GETS(d,getNul(),getB(),getA());
        ASSERT_TRUE(nul(a3Nul));
    }

    TEST(MacroTest, UnconstCalltest) {
        struct A {
            WRD_DECL_THIS(A)

        public:
            wbool foo() {
                return true;
            }
            wbool foo() const WRD_UNCONST_FUNC(foo())
        } a;

        const A& aConst = a;
        ASSERT_TRUE(aConst.foo());
    }
}}
