#include "../../../namuSyntaxTest.hpp"

using namespace namu;
using namespace std;

namespace {
    struct akaTest : public namuSyntaxTest {};
}

TEST_F(akaTest, defaultDef) {
    make().parse(R"SRC(
        aka console c
    )SRC").shouldParsed(true);
    shouldVerified(false);
}

TEST_F(akaTest, defaultDef2) {
    make().parse(R"SRC(
        aka console
        c
    )SRC").shouldParsed(false);
}

TEST_F(akaTest, defaultDef3) {
    make().parse(R"SRC(
        aka sys.console c
    )SRC").shouldParsed(true);
    shouldVerified(false);
}

TEST_F(akaTest, defaultDef4) {
    make().parse(R"SRC(
        aka sys.con c
    )SRC").shouldVerified(true);
}

TEST_F(akaTest, defaultDef5) {
    make().parse(R"SRC(
        aka sys.console
    )SRC").shouldParsed(true);
    shouldVerified(false);
}

TEST_F(akaTest, deducedAllDefNegative) {
    make().parse(R"SRC(
    aka console.*
    )SRC").shouldParsed(false);
}

TEST_F(akaTest, deducedAllDefNegative2) {
    make().parse(R"SRC(
        aka console. *
    )SRC").shouldParsed(false);
    shouldVerified(false);
}

TEST_F(akaTest, deducedAllDefNegative3) {
    make().parse(R"SRC(
        aka console.
         *
    )SRC").shouldParsed(false);
}

TEST_F(akaTest, deducedAllDefNegative4) {
    make().parse(R"SRC(
        aka console.
    )SRC").shouldParsed(false);
}

TEST_F(akaTest, withDefvar) {
    make().parse(R"SRC(
        aka a int b
    )SRC").shouldParsed(false);
}

TEST_F(akaTest, withDefvar2) {
    make().parse(R"SRC(
        aka a b
    )SRC").shouldParsed(true);
}

TEST_F(akaTest, akaHelloWorld) {
    make().parse(R"SRC(
        aka sys.con
        main() void
            con.print("hello world!")
    )SRC").shouldVerified(true);
    run();
}

TEST_F(akaTest, akaHelloWorld2) {
    make().parse(R"SRC(
        aka sys.con c
        aka sys.con
        main() void
            c.print("hello world x1\n")
            con.print("hello world x2\n")
    )SRC").shouldVerified(true);
    run();
}

/* TODO:
TEST_F(akaTest, withDeffunc) {
    make().parse(R"SRC(
        aka foo(a int, b str)
            doSomething()
        -> b)SRC").shouldParsed(true);
}

TEST_F(akaTest, withDeffunc2) {
    make().parse(R"SRC(
        aka foo(a int, b str)
            doSomething()
         -> b
    )SRC").shouldParsed(true);
    ASSERT_TRUE(getReport().hasWarn());
}

TEST_F(akaTest, withDeffunc3) {
    make().parse(R"SRC(
        aka foo(a int, b str)
            doSomething()
        ->
         b
    )SRC").shouldParsed(false);
}
}*/
