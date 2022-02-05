#include "../../syntaxTest.hpp"

using namespace wrd;
using namespace std;

namespace {
    struct syntaxAkaTest : public syntaxTest {};
}

TEST_F(syntaxAkaTest, defaultDef) {
    make().parse(R"SRC(
aka console -> c
)SRC").expect(true);
    make().parse(R"SRC(
aka console ->
c
)SRC").expect(false);
    make().parse(R"SRC(
aka sys.console -> c
)SRC").expect(true);
    make().parse(R"SRC(
aka sys.console ->
c
)SRC").expect(false);
}

TEST_F(syntaxAkaTest, deducedAllDefNegative) {
    make().parse(R"SRC(
aka console.*
)SRC").expect(false);
    make().parse(R"SRC(
aka console. *
)SRC").expect(false);
    make().parse(R"SRC(
aka console.
 *
)SRC").expect(false);
    make().parse(R"SRC(
aka console.
)SRC").expect(false);
}

TEST_F(syntaxAkaTest, withDefvar) {
    make().parse(R"SRC(
aka a int -> b
    )SRC").expect(true);

    make().parse(R"SRC(
aka a -> b
    )SRC").expect(true);
}

TEST_F(syntaxAkaTest, withDeffunc) {
    make().parse(R"SRC(
aka foo(a int, b str)
    doSomething()
-> b)SRC").expect(true);
}

TEST_F(syntaxAkaTest, withDeffunc2) {
    make().parse(R"SRC(
aka foo(a int, b str)
    doSomething()
 -> b)SRC").expect(true);
    ASSERT_FALSE(getReport()); // rpt.operator bool() return true if error exists
    ASSERT_TRUE(getReport().hasWarn());
}

TEST_F(syntaxAkaTest, withDeffunc3) {
    make().parse(R"SRC(
aka foo(a int, b str)
    doSomething()
->
 b)SRC").expect(false);
}
