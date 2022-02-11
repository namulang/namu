#include "../../../syntaxTest.hpp"

using namespace wrd;
using namespace std;

namespace {
    struct akaTest : public syntaxTest {};
}

TEST_F(akaTest, defaultDef) {
    make().parse(R"SRC(
        aka console -> c
    )SRC").expect(true);
}

TEST_F(akaTest, defaultDef2) {
    make().parse(R"SRC(
        aka console ->
        c
    )SRC").expect(false);
}

TEST_F(akaTest, defaultDef3) {
    make().parse(R"SRC(
        aka sys.console -> c
    )SRC").expect(true);
}

TEST_F(akaTest, defaultDef4) {
    make().parse(R"SRC(
        aka sys.console ->
        c
    )SRC").expect(false);
}

TEST_F(akaTest, deducedAllDefNegative) {
    make().parse(R"SRC(
    aka console.*
        )SRC").expect(false);
}

TEST_F(akaTest, deducedAllDefNegative2) {
    make().parse(R"SRC(
        aka console. *
    )SRC").expect(false);
}

TEST_F(akaTest, deducedAllDefNegative3) {
    make().parse(R"SRC(
        aka console.
         *
    )SRC").expect(false);
}

TEST_F(akaTest, deducedAllDefNegative4) {
    make().parse(R"SRC(
        aka console.
    )SRC").expect(false);
}

TEST_F(akaTest, withDefvar) {
    make().parse(R"SRC(
        aka a int -> b
    )SRC").expect(true);
}

TEST_F(akaTest, withDefvar2) {
    make().parse(R"SRC(
        aka a -> b
    )SRC").expect(true);
}

TEST_F(akaTest, withDeffunc) {
    make().parse(R"SRC(
        aka foo(a int, b str)
            doSomething()
        -> b)SRC").expect(true);
}

TEST_F(akaTest, withDeffunc2) {
    make().parse(R"SRC(
        aka foo(a int, b str)
            doSomething()
         -> b
    )SRC").expect(true);
    ASSERT_FALSE(getReport()); // rpt.operator bool() return true if error exists
    ASSERT_TRUE(getReport().hasWarn());
}

TEST_F(akaTest, withDeffunc3) {
    make().parse(R"SRC(
        aka foo(a int, b str)
            doSomething()
        ->
         b
    )SRC").expect(false);
}
