#include "../../syntaxTest.hpp"

using namespace wrd;
using namespace std;

namespace {
    struct syntaxAkaTest : public syntaxTest {};
}

TEST_F(syntaxAkaTest, defaultDef) {
    parse(R"SRC(
aka console -> c
)SRC");
    parseFail(R"SRC(
aka console ->
c
)SRC");
    parse(R"SRC(
aka sys.console -> c
)SRC");
    parseFail(R"SRC(
aka sys.console ->
c
)SRC");
}

TEST_F(syntaxAkaTest, deducedAllDef) {
    parse(R"SRC(
aka console.*
)SRC");
    parseFail(R"SRC(
aka console. *
)SRC");
    parseFail(R"SRC(
aka console.
 *
)SRC");
    parseFail(R"SRC(
aka console.
)SRC");
}

TEST_F(syntaxAkaTest, withDefvar) {
    parse(R"SRC(
aka a int -> b
    )SRC");

    parse(R"SRC(
aka a -> b
    )SRC");
}

TEST_F(syntaxAkaTest, withDeffunc) {
    parse(R"SRC(
aka foo(a int, b str)
    doSomething()
-> b)SRC");
}

TEST_F(syntaxAkaTest, withDeffunc2) {
    errReport rpt;
    parse(R"SRC(
aka foo(a int, b str)
    doSomething()
 -> b)SRC", rpt);
    ASSERT_FALSE(rpt); // rpt.operator bool() return true if error exists
    ASSERT_TRUE(rpt.hasWarn());
}

TEST_F(syntaxAkaTest, withDeffunc3) {
    parseFail(R"SRC(
aka foo(a int, b str)
    doSomething()
->
 b)SRC");
}
