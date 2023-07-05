#include "../../../namuSyntaxTest.hpp"

using namespace namu;
using namespace std;

namespace {
    struct genericsTest : public namuSyntaxTest {};
}

TEST_F(genericsTest, simpleDefineGenerics) {
    // as, defObj
    make().parse(R"SRC(
        def object<T>
            foo() str
                ret print(1 as T)

        main() int
            a := object<str>()
            ret a.foo() == "1"
    )SRC").shouldVerified(true);

    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 1);
}

TEST_F(genericsTest, defineGenerics) {
    // defVar, func
    make().parse(R"SRC(
        def object<e>
            age e
            foo(num e) e
                ret age + num as e

        main() int
            a := object<int>()
            ret a.foo(2) as str == "2"
    )SRC").shouldVerified(true);

    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 1);
}

TEST_F(genericsTest, defineGenerics1) {
    make().parse(R"SRC(
        def object<T>
            foo(a T) T
                age := T() + T()
                ret a + age + boo()
            boo() T
                ret T()

        main() int
            a := object<int>()
            print(a.foo(2) as str) == "2"
    )SRC").shouldVerified(true);

    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 1);
}

TEST_F(genericsTest, genericTwice1) {
    make().parse(R"SRC(
        def object<T>
            foo() void
                print("1")

        main() void
            a := object<str>()
            b := object<bool>()
            c := object<flt>() // run 'b.foo()' occurs F/C
    )SRC").shouldVerified(true);
    run();
    node& object = getSubPack().sub("object");
    str a = object.run(args( narr {*new nStr()}));
    ASSERT_TRUE(a);
    str b = object.run(args( narr {*new nFlt()}));
    ASSERT_TRUE(b);
    ASSERT_NE(&a.get(), &b.get());

    node& aFoo = a->sub("foo");
    ASSERT_FALSE(nul(aFoo));
    node& bFoo = b->sub("foo");
    ASSERT_FALSE(nul(bFoo));
    ASSERT_NE(&aFoo, &bFoo);
}

TEST_F(genericsTest, genericTwice2Negative) {
    negative().make().parse(R"SRC(
        def object<T>
            foo(val T) T
                age := T()
                print((val + age) as T)
                ret val + age

        main() int
            a := object<int>()
            b := object<str>() // run 'b.foo()' occurs F/C
            ret b.foo("3.5") == "3.5"
    )SRC").shouldParsed(true);
    shouldVerified(false);
}

TEST_F(genericsTest, genericTwice2) {
    make().parse(R"SRC(
        def object<T>
            foo(val T) T
                age := T()
                print((val + age) as str)
                ret val + age

        main() int
            a := object<int>()
            b := object<str>() // run 'b.foo()' occurs F/C
            ret b.foo("3.5") == "3.5"
    )SRC").shouldVerified(true);
    str ret = run();
    ASSERT_TRUE(ret);
    ASSERT_EQ(ret->cast<nint>(), 1);
}

TEST_F(genericsTest, simpleUseGenerics) {
    make().parse(R"SRC(
        def object<T>
            foo(msg T) str
                print(msg)
                ret msg

        main() int
            o := object<str>()
            res := o.foo("hello generics!\n")
            ret res == "hello generics!\n"
    )SRC").shouldVerified(true);

    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res->cast<nint>(), 1);
}

TEST_F(genericsTest, implicitReturnTest) {
    make().parse(R"SRC(
        def pakuman<T>
            foo() T
                "hello " + "world"

        main() int
            p := pakuman<str>()
            p.foo() == "hello world"
    )SRC").shouldVerified(true);
    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res->cast<nint>(), 1);
}

TEST_F(genericsTest, simpleUseGenerics2) {
    make().parse(R"SRC(
        def object<T>
            foo(val T) T
                age := T()
                print((val + age) as T)
                ret val + age

        main() int
            b := object<str>()
            ret b.foo("3.5") == "3.5"
    )SRC").shouldVerified(true);

    str ret = run();
    ASSERT_TRUE(ret);
    ASSERT_EQ(ret->cast<nint>(), 1);
}

TEST_F(genericsTest, genericNegative) {
    make().negative().parse(R"SRC(
        def object<T>
            foo(val T) T
                age := T()
                print((val + age) as T)
                ret val + age

        main() int
            b := object<int>() // error at print(int)
            ret b.foo(3.5)
    )SRC").shouldVerified(false);
}

TEST_F(genericsTest, genericParameter2) {
    make().parse(R"SRC(
        def obj<T1, T2>
            foo(v1 T1, v2 T2) str
                ret "v1=" + v1 as str + ", v2=" + v2 as str

        main() int
            ret obj<int, str>().foo(3, "hello") == "v1=3, v2=hello"
    )SRC").shouldVerified(true);

    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 1);
}

TEST_F(genericsTest, assignDifferentParameterizedTypeNegative) {
    make().negative().parse(R"SRC(
        def A<T>
            age T
        main() void
            a A<int>
            a = A<flt>()
    )SRC").shouldVerified(false);
}
