#include "../../../namuSyntaxTest.hpp"

using namespace namu;
using namespace std;

namespace {
    struct forExprTest : public namuSyntaxTest {};
}

TEST_F(forExprTest, simpleTest) {
    make().parse(R"SRC(
        main() int
            sum := 0
            for n in {1, 2, 3}
                print("sum=" + sum as str + ", n=" + n as str + "\n")
                sum = sum + n
            ret sum
    )SRC").shouldVerified(true);
    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 6);
}

TEST_F(forExprTest, simpleTest2) {
    make().parse(R"SRC(
        main() int
            sum := 0
            for n in {1, 2, 3}
                sum = sum + n
                print("sum=" + sum as str + ", n=" + n as str + "\n")
            ret sum
    )SRC").shouldVerified(true);
    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 6);
}

TEST_F(forExprTest, testWhatFromFunc) {
    make().parse(R"SRC(
        foo() int[]
            ret {1, 2, 3}

        main() int
            sum := 0
            for n in foo()
                sum = sum + n
                print("sum=" + sum as str + ", n=" + n as str + "\n")

            ret sum
    )SRC").shouldVerified(true);
    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 6);
}

TEST_F(forExprTest, putAkaMiddleOfLoop) {
    make().parse(R"SRC(
        foo() int[]
            ret {1, 2, 3}

        main() int
            sum := 0
            for n in foo()
                sum = sum + n
                print("sum=" + sum as str + ", n=" + n as str + "\n")

            ret sum
    )SRC").shouldVerified(true);
    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 6);
}

TEST_F(forExprTest, sequenceLoop) {
    make().parse(R"SRC(
        main() int
            sum := 0
            for n in 2..5
                sum = sum + n
                print("sum=" + sum as str + ", n=" + n as str + "\n")

            ret sum
    )SRC").shouldVerified(true);
    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 9);
}

TEST_F(forExprTest, validationCheck) {
    make().negative().parse(R"SRC(
        main() str
            for n in {1, 2, 3}
                print(n)
    )SRC").shouldParsed(true);
    shouldVerified(false);
}

TEST_F(forExprTest, loopObjects) {
    make().parse(R"SRC(
        def person1
            name := "unknown"
            age := 0
            say() str
                print("I'm " + name + " and " + age as str + " years old.\n")

        main() int
            p1 person1
            p2 := person1()
            p3 := person1()
            p1.name = "Chales"
            p1.age = 36
            p2.name = "Mario"
            p2.age = 45
            p3.name = "Peach"
            p3.age = 44

            sum := ""
            for p in {p1, p2, p3}
                sum = sum + p.say()
            ret sum == "I'm Chales and 36 years old.\n" + "I'm Mario and 45 years old.\n" + "I'm Peach and 44 years old.\n"
    )SRC").shouldVerified(true);

    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res->cast<nint>(), 1);
}

TEST_F(forExprTest, useObjectAsContainer) {
    make().parse(R"SRC(
        def person
            name := ""

        main() void
            p1 := person()
            p1.name = "Chales"
            people := {person(), p1}

            for p in people
                print(p.name)
    )SRC").shouldVerified(true);
    run();
}

TEST_F(forExprTest, returnMiddleOfLoop) {
    make().parse(R"SRC(
        def person
            name := ""

        main() int
            p1 := person()
            p1.name = "Chales"

            for p in {p1, person()}
                ret p.name == "Chales"
            ret 0
    )SRC").shouldVerified(true);
    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 1);
}

TEST_F(forExprTest, returnMiddleOfLoop1) {
    make().parse(R"SRC(
        def person
            name := ""

        main() int
            p1 := person()
            p1.name = "Chales"

            res := (for p in {p1, person()}
                if p.name != p1.name
                    break
                p.name
            )
            ret (res[0] + " Lee") == "Chales Lee"
    )SRC").shouldVerified(true);
    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 1);
}

TEST_F(forExprTest, returnMiddleOfLoop1WithoutParenthesis) {
    make().parse(R"SRC(
        def person
            name := ""

        main() int
            p1 := person()
            p1.name = "Chales"

            res := for p in {p1, person()}
                ret p1.name == "Chales"
            ret 0
    )SRC").shouldVerified(true);
    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 1);
}

TEST_F(forExprTest, retMiddleOfLoop) {
    make().parse(R"SRC(
        def person
            name := ""

        main() int
            p1 := person()
            p1.name = "Chales"

            res := (for p in {p1, person()}
                p1.name
            )
            ret res + " Lee" == "Chales Lee"
    )SRC").shouldVerified(true);
    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 1);
}

TEST_F(forExprTest, retMiddleOfLoopWithoutParenthesis) {
    make().parse(R"SRC(
        def person
            name := ""

        main() int
            p1 := person()
            p1.name = "Chales"

            res := for p in {p1, person()}
                p1.name
            ret res + " Lee" == "Chales Lee"
    )SRC").shouldVerified(true);
    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 1);
}

TEST_F(forExprTest, retMiddleOfLoopNegative) {
    make().negative().parse(R"SRC(
        def person
            name := ""

        main() int
            p1 := person()
            p1.name = "Chales"

            res := 0
            res = (for p in {p1, person()}
                p1.name
            )
            ret res
    )SRC").shouldVerified(false);
}

TEST_F(forExprTest, evalForExprWithoutRet) {
    make().parse(R"SRC(
        def person
            name := ""

        main() int
            p1 := person()
            p1.name = "Chales"

            res := (for p in {p1, person()}
                p.name
            )
            ret res == ""
    )SRC").shouldVerified(true);
    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 1);
}

TEST_F(forExprTest, simpleBreakTest) {
    make().parse(R"SRC(
        main() int
            res := (for n in 1..10
                break 5
            )
            ret res
    )SRC").shouldVerified(true);
    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 5);
}

TEST_F(forExprTest, simpleBreakTestWithoutParenthesis) {
    make().parse(R"SRC(
        main() int
            res := for n in 1..10
                break 5
            ret res
    )SRC").shouldVerified(true);
    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 5);
}

TEST_F(forExprTest, retForExpr) {
    make().parse(R"SRC(
        main() int
            for n in 1..10
                if true
                    5
                else
                    7
    )SRC").shouldVerified(true);
    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 5);
}

TEST_F(forExprTest, breakIsNotExpressionNegative) {
    make().negative().parse(R"SRC(
        main() int
            for n in 1..5
                foo(break 3)
    )SRC").shouldParsed(false);
}

TEST_F(forExprTest, nextIsNotExpressionNegative) {
    make().negative().parse(R"SRC(
        main() int
            for n in 1..5
                foo(next)
    )SRC").shouldParsed(false);
}

TEST_F(forExprTest, breakInsideOfFor) {
    make().parse(R"SRC(
        main() int
            for n in 1..5
                break 7
    )SRC").shouldVerified(true);

    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 7);
}

TEST_F(forExprTest, breakInsideOfIfExpr) {
    make().parse(R"SRC(
        main() void
            for n in 1..5
                if n == 3
                    break 7
    )SRC").shouldVerified(true);

    str res = run();
    ASSERT_TRUE(res);
    ASSERT_TRUE(res->isSub<nVoid>());
}

TEST_F(forExprTest, breakInsideOfIfExprNegative) {
    make().negative().parse(R"SRC(
        main() int
            // this stmt returns what forExpr evaluated.
            // but its type is void. because ifExpr doesn't have else
            // block.
            for n in 1..5
                if n == 3
                    break 7
    )SRC").shouldVerified(false);
}

TEST_F(forExprTest, breakInsideOfIfExpr2) {
    make().parse(R"SRC(
        main() int
            for n in 1..5
                if n == 3
                    break 7
                else
                    n
    )SRC").shouldVerified(true);

    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 7);
}

TEST_F(forExprTest, breakNestedForLoop) {
    make().parse(R"SRC(
        main() int
            sum := 0
            for n in 0..7
                for n2 in 0..4
                    ++sum
                    if sum > 15
                        break
                if sum > 15
                    break
            sum
    )SRC").shouldVerified(true);

    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 16);
}

TEST_F(forExprTest, evalOfForLoop) {
    make().parse(R"SRC(
        main() int
            sum := 0
            ans := for n in 0..8
                if sum > 3
                    break "hello"
                ++sum as str
            ret ans == "hello"
    )SRC").shouldVerified(true);

    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 1);
}

TEST_F(forExprTest, evalOfForLoopNegative) {
    make().negative().parse(R"SRC(
        main() int
            sum := 0
            for n in 0..8
                if sum > 3
                    break "hello"
                ++sum
    )SRC").shouldVerified(false);
}

TEST_F(forExprTest, evalOfForLoopNegative2) {
    make().negative().parse(R"SRC(
        def a
            foo() void
                ret

        main() int
            sum := 0
            for n in 0..8
                if sum > 3
                    break a()
                ++sum
    )SRC").shouldVerified(false);
}
 
TEST_F(forExprTest, evalOfForLoopNegative3) {
    make().negative().parse(R"SRC(
        def a
            foo() void
                ret

        main() int
            sum := 0
            answer := for n in 0..8
                if sum > 11
                    if true
                        break "hello"
                ++sum
    )SRC").shouldVerified(false);
}

TEST_F(forExprTest, evalOfForLoopNegative4) {
    make().negative().parse(R"SRC(
        def a
            foo() void
                ret

        main() int
            sum := 0
            for n in 0..8
                if sum > 3
                    break a()
                ++sum
            sum
    )SRC").shouldVerified(true);

    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 4);
}

TEST_F(forExprTest, evalOfForLoopNegative5) {
    make().negative().parse(R"SRC(
        main() str
            sum := 0
            answer := for n in 0..8
                if sum > 11
                    if true
                        break "hello"
                ++sum
    )SRC").shouldVerified(false);
}

TEST_F(forExprTest, evalOfForLoopIntAndBoolIsCompatible) {
    make().parse(R"SRC(
        main() int
            sum := 0
            answer := for n in 0..8
                if sum > 11
                    if true
                        break false
                ++sum
    )SRC").shouldVerified(true);

    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 8);
}

TEST_F(forExprTest, evalOfForLoopIntAndBoolIsCompatible2) {
    make().parse(R"SRC(
        main() int
            sum := 0
            answer := for n in 0..8
                if sum > 3
                    if true
                        break false
                ++sum
    )SRC").shouldVerified(true);

    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res->getType(), ttype<nInt>::get());
    ASSERT_EQ(res.cast<nint>(), 0);
}

TEST_F(forExprTest, defAssignWhatLoops) {
    make().parse(R"SRC(
        main() int
            a := for n in 0..2
                n++
            ret a
    )SRC").shouldVerified(true);

    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res->cast<nint>(), 1);
}
