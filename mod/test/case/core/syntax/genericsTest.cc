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
                return sys.con.print(1 as T)

        main() str
            a := object<str>()
            return a.foo()
    )SRC").shouldVerified(true);
    ASSERT_EQ(run().cast<std::string>(), "1");
}

TEST_F(genericsTest, defineGenerics) {
    // defVar, func
    make().parse(R"SRC(
        def object<e>
            age e
            foo(num e) e
                return age + num as e

        main() str
            a := object<int>()
            return a.foo(2) as str
    )SRC").shouldVerified(true);
    str ret = run();
    ASSERT_EQ(ret.cast<std::string>(), "2");
}

TEST_F(genericsTest, defineGenerics1) {
    make().parse(R"SRC(
        def object<T>
            foo(a T) T
                age := T() + T()
                return a + age + boo()
            boo() T
                return T()

        main() void
            a := object<int>()
            sys.con.print(a.foo(2) as str)
    )SRC").shouldVerified(true);
    str ret = run();
    ASSERT_EQ(ret.cast<std::string>(), "2");
}

TEST_F(genericsTest, genericTwice1) {
    make().parse(R"SRC(
        def object<T>
            foo() void
                sys.con.print("1")

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

TEST_F(genericsTest, genericTwice2) { // need deepClone()
    make().parse(R"SRC(
        def object<T>
            foo(val T) T
                age := T()
                sys.con.print((val + age) as T)
                return val + age

        main() str
            a := object<int>()
            b := object<str>() // run 'b.foo()' occurs F/C
            return b.foo("3.5")
    )SRC").shouldVerified(true);
    str ret = run();
    ASSERT_FALSE(nul(ret));
    ASSERT_EQ(ret->cast<std::string>(), "3.5");
}

TEST_F(genericsTest, simpleUseGenerics) {
    make().parse(R"SRC(
        def object<T>
            foo(msg T) str
                sys.con.print(msg)
                return msg

        main() str
            o := object<str>()
            res := o.foo("hello generics!\n")
            return res
    )SRC").shouldVerified(true);
    str res = run();
    ASSERT_TRUE(res);
    std::string msg = res->cast<std::string>();
    ASSERT_EQ(msg, "hello generics!\n");
    NAMU_I("msg from generics: %s", msg.c_str());
}
/*
TEST_F(genericsTest, genericNegative) {
    make().parse(R"SRC(
        def object<T>
            foo(val T) T
                age := T()
                sys.con.print((val + age) as T)
                return val + age

        main() str
            a := object<int>()
            b := object<str>() // run 'b.foo()' occurs F/C
            return b.foo("3.5")
    )SRC").shouldVerified(true);
    str ret = run();
    ASSERT_FALSE(nul(ret));
    ASSERT_EQ(ret->cast<std::string>(), "3.5");
}
*/
