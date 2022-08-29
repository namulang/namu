#include "../../../namuSyntaxTest.hpp"

using namespace namu;
using namespace std;

namespace {
    struct defObjExprTest : public namuSyntaxTest {};
}

TEST_F(defObjExprTest, simpleDefineObject) {
    make().parse(R"SRC(
        def A
            foo() void
                sys.con.print("hello")
    )SRC").shouldVerified(true);
    run();
}

TEST_F(defObjExprTest, simpleDefineObject2) {
    make().parse(R"SRC(
        def A
            foo() void
                sys.con.print("hello")
        main() void
            a A
            a.foo()
    )SRC").shouldVerified(true);
    run();
}

TEST_F(defObjExprTest, simpleDefineObjectNegative) {
    negative().make().parse(R"SRC(
        def A
            foo() void
                sys.con.print("hello")
        main() void
            a B
            a.foo()
    )SRC").shouldParsed(true);
    shouldVerified(false);
}

TEST_F(defObjExprTest, assignMemberVariable) {
    make().parse(R"SRC(
        def obj
            index := 5

        main() int
            o := obj()
            o.index = 2
            sys.con.print(o.index as str)
            o.index
    )SRC").shouldVerified(true);
    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 2);
}
