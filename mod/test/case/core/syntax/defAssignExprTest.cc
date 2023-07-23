#include "../../../namuSyntaxTest.hpp"

using namespace namu;
using namespace std;

namespace {
    struct defAssignExprTest : public namuSyntaxTest {};
}

TEST_F(defAssignExprTest, simpleGlobalDefAssign) {
    // control group.
    make().parse(R"SRC(
        age int // age is age
        main() int // main is also a main
            age := 5
            ret 0
    )SRC").shouldVerified(true);
    scope& owns = (scope&) (((scopes&) getSlot().subs()).getContainer());
    scope& shares = (scope&) (((scopes&) getSlot().subs()).getNext().getContainer());
    ASSERT_FALSE(nul(shares));
    ASSERT_FALSE(nul(owns));
    ASSERT_EQ(owns.len(), 1);
    ASSERT_EQ(shares.len(), 3);

    run();
    ASSERT_EQ(getSubPack().sub<nInt>("age").cast<int>(), 0);
}

TEST_F(defAssignExprTest, simpleLocalDefAssign) {
    // control group.
    make().parse(R"SRC(
        age int // age is age
        main() int // main is also a main
            age = 3
            age := 5
            age = 2
            ret 0
    )SRC").shouldVerified(true);
    run();
    ASSERT_EQ(getSubPack().sub("age").cast<int>(), 3);
}

TEST_F(defAssignExprTest, testCircularDependencies) {
    make("holymoly").negative().parse(R"SRC(
        pack holymoly

        a := c
        b := a
        c := b // type can't be defined.

        main() int
            ret 0
    )SRC").shouldParsed(true);
    shouldVerified(false);
    // however when runs it, it throws an error.
}

TEST_F(defAssignExprTest, testNearCircularDependencies) {
    make("holymoly").parse(R"SRC(
        pack holymoly

        c := 1 // type can be defined.
        a := c
        b := a

        main() int
            print(a as str)
            print(b as str)
            ret 0
    )SRC").shouldParsed(true);
    shouldVerified(true);
    // however when runs it, it throws an error.
    // because assigning 1 to c will be done after evaluating of assignment of the 'a'.
}

TEST_F(defAssignExprTest, testDefAssign1) {
    make().parse(R"SRC(
        foo() int
            ret a = 2

        a := foo() + 5

        main() int
            print("a=" + a as str)
            ret 0
    )SRC").shouldVerified(true);
    run();
}

TEST_F(defAssignExprTest, defAssignInObjectRefersInvalidFuncNegative) {
    negative().make().parse(R"SRC(
        nickname := foo()

        foo() str
            print("I'm foo!\n")
            ret 1 // this is invalid function.

        main() void
            print("your nickname is " + nickname)
    )SRC").shouldParsed(true);
    shouldVerified(false);
}

TEST_F(defAssignExprTest, defAssignInObjectRefersInvalidFuncNegative2) {
    negative().make().parse(R"SRC(
        nickname := boo() // refers the func that doesn't exist.

        foo() str
            print("I'm foo!\n")
            ret 1 // this is invalid function.

        main() void
            print("your nickname is " + nickname)
    )SRC").shouldParsed(true);
    shouldVerified(false);
}

TEST_F(defAssignExprTest, defAssignRefersItsIdentifierNegative) {
    negative().make().parse(R"SRC(
        aka sys.con
        con := con.add(1, 2)

        main() void
            print("res=" + con)
    )SRC").shouldParsed(true);
    shouldVerified(false);
}

TEST_F(defAssignExprTest, defAssignRefersItsIdentifierNegative2) {
    negative().make().parse(R"SRC(
        aka sys.con
        con := con.add(1, 2)

        main() void
            print("res=" + con)
    )SRC").shouldParsed(true);
    shouldVerified(false);
}

TEST_F(defAssignExprTest, defAssignRefersItsIdentifierNegative3) {
    negative().make().parse(R"SRC(
        aka sys.con
        con := con.add(1, 2)

        main() void
            print("res=" + con.add(1, 2))
    )SRC").shouldParsed(true);
    shouldVerified(false);
}

TEST_F(defAssignExprTest, defAssignAsParameterNegative) {
    make().negative().parse(R"SRC(
        def f
            foo(a int, b int) int
                ret a + b

        main() void
            f1 f
            a = f1.foo(a := 5, 5)
    )SRC").shouldParsed(true);
    shouldVerified(false);
}

TEST_F(defAssignExprTest, defAssignAsParameterNegative2) {
    make().negative().parse(R"SRC(
        def f
            foo(a int, b int) int
                ret a + b

        main() void
            f1 f
            a = f1.foo((a := 5), 5)
    )SRC").shouldParsed(true);
    shouldVerified(false);
}

TEST_F(defAssignExprTest, defAssignAsParameterNegative3) {
    make().negative().parse(R"SRC(
        def f
            foo(a int, b int) int
                ret a + b

        main() int
            f1 f
            a2 = f1.foo(a2 := 5, 5)
            a2 = a2 + a
    )SRC").shouldVerified(false);
}

TEST_F(defAssignExprTest, defAssignAsParameter) {
    make().parse(R"SRC(
        def f
            foo(a int, b int) int
                ret a + b

        main() int
            f1 f
            a2 := f1.foo(a := 5, 5)
            a2 = a2 + a
    )SRC").shouldParsed(true);
    shouldVerified(true);
}

TEST_F(defAssignExprTest, defAssignDefAssignedValue) {
    make().parse(R"SRC(
        def a
            age int
        main() int
            a1 := a2 := a()
            ret a1.age
    )SRC").shouldVerified(true);

    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 0);
}

TEST_F(defAssignExprTest, defAssignVoidNegative) {
    make().negative().parse(R"SRC(
        main() void
            a := void()
    )SRC").shouldVerified(false);
}

TEST_F(defAssignExprTest, defAssignVoidNegative2) {
    make().negative().parse(R"SRC(
        foo() void
            ret

        main() void
            a := for n in 0..1
                foo()
            ret a
    )SRC").shouldVerified(false);
}

TEST_F(defAssignExprTest, defAssignIfWithoutElseNegative) {
    make().negative().parse(R"SRC(
        main() void
            a := if true
                "hello"
    )SRC").shouldVerified(false);
}

TEST_F(defAssignExprTest, defAssignIfWithElse) {
    make().parse(R"SRC(
        main() int
            a := if true
                "hello"
            else
                "world"
            ret a == "hello"
    )SRC").shouldVerified(true);

    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 1);
}

TEST_F(defAssignExprTest, defAssignEvalOfSetElemConversion) {
    make().parse(R"SRC(
        foo() int
            0
        boo() int
            1
        main() int
            arr := {1, 2}
            val := arr[foo()] -= boo()
            val == true
            // why val is bool type?:
            //  because of 'setElemConversion', arr[foo()] -= boo() will translate to,
            //      arr.set(foo(), arr.get(foo()) - boo())
            //  . and set() returns 'true' as boolean  when its job successed.
    )SRC").shouldVerified(true);

    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), true);
}

TEST_F(defAssignExprTest, defAssignAtIf) {
    make().parse(R"SRC(
        main() int
            if res := 0.3
                ret res == 0.3
            ret 0
    )SRC").shouldVerified(true);

    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 1);
}
