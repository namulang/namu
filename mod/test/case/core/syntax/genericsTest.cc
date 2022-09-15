#include "../../../namuSyntaxTest.hpp"

using namespace namu;
using namespace std;

namespace {
    struct genericsTest : public namuSyntaxTest {};
}

TEST_F(genericsTest, simpleDefineGenerics) {
    make().parse(R"SRC(
        def object<T>
            foo() str
                sys.con.print(1 as T)

        main() str
            a := object<str>()
            return a.foo()
    )SRC").shouldVerified(true);
    ASSERT_EQ(run().cast<std::string>(), "1");
}

TEST_F(genericsTest, defineGenerics) {
    make().parse(R"SRC(
        def object<e>
            age e
            foo() str
                return age + 1 as str

        main() str
            a := object<int>()
            return a.foo()
    )SRC").shouldVerified(true);
    str ret = run();
    ASSERT_EQ(ret.cast<std::string>(), "01");
}

TEST_F(genericsTest, defineGenerics1) {
    make().parse(R"SRC(
        def object<T>
            age T
            foo(a T) T
                return a + age

        main() void
            a := object<int>()
            sys.con.print(a.foo(2) as str)
    )SRC").shouldVerified(true);
}

TEST_F(genericsTest, makeGenericTwice) { // need deepClone()
    make().parse(R"SRC(
        def object<T>
            foo() void
                sys.con.print(1 as T)

        main() void
            a := object<str>()
            b := object<flt>() // run 'b.foo()' occurs F/C
            a.foo()
    )SRC").shouldVerified(true);
}

/*TEST_F(genericsTest, simpleUseGenerics) {
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
}*/
