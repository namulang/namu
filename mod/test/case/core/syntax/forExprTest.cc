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
                sys.con.print("sum=" + sum + ", n=" + n + "\n")
                sum = sum + n
            return sum
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
                sys.con.print("sum=" + sum + ", n=" + n + "\n")
            return sum
    )SRC").shouldVerified(true);
    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 6);
}

TEST_F(forExprTest, testWhatFromFunc) {
    make().parse(R"SRC(
        foo() int[]
            return {1, 2, 3}

        main() int
            sum := 0
            for n in foo()
                sum = sum + n
                sys.con.print("sum=" + sum + ", n=" + n + "\n")

            return sum
    )SRC").shouldVerified(true);
    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 6);
}

TEST_F(forExprTest, putAkaMiddleOfLoop) {
    make().parse(R"SRC(
        foo() int[]
            return {1, 2, 3}

        main() int
            sum := 0
            for n in foo()
                sum = sum + n
                aka sys.con
                con.print("sum=" + sum + ", n=" + n + "\n")

            return sum
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
                sys.con.print("sum=" + sum + ", n=" + n + "\n")

            return sum
    )SRC").shouldVerified(true);
    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 9);
}

TEST_F(forExprTest, validationCheck) {
    make().negative().parse(R"SRC(
        main() str
            for n in {1, 2, 3}
                sys.con.print(n)
    )SRC").shouldParsed(true);
    shouldVerified(false);
}

TEST_F(forExprTest, loopObjects) {
    make().parse(R"SRC(
        def person1
            name := "unknown"
            age := 0
            say() str
                sys.con.print("I'm " + name + " and " + age + " years old.\n")

        main() str
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
            return sum
    )SRC").shouldVerified(true);
    /*str ret = run();
    ASSERT_TRUE(ret);
    std::string answer =    "I'm Chales and 36 years old.\n"
                            "I'm Mario and 45 years old.\n"
                            "I'm Peach and 44 years old.\n";
    std::string msg = ret->cast<std::string>();
    ASSERT_EQ(ret->cast<std::string>(), answer);*/
}

TEST_F(forExprTest, loopObjectsNegative) {
    make().negative().parse(R"SRC(
        def person
            name := "unknown"
            age := 0
            say() str
                sys.con.print("I'm " + name + " and " + age + " years old.\n")

        main() str
            p1 person
            p2 := person()
            p3 := person()
            p1.name = "Chales"
            p1.age = 36
            p2.name = "Mario"
            p2.age = 45
            p3.name = "Peach"
            p3.age = 44

            p1.say()

            sum := ""
            for p in {p1, p2, p3}
                sum = sum + p.say1()
            return sum
    )SRC").shouldVerified(false);
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
                sys.con.print(p.name)
    )SRC").shouldVerified(true);
    run();
}

TEST_F(forExprTest, returnMiddleOfLoop) {
    make().parse(R"SRC(
        def person
            name := ""

        main() str
            p1 := person()
            p1.name = "Chales"

            for p in {p1, person()}
                return p.name
            return ""
    )SRC").shouldVerified(true);
    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<std::string>(), "Chales");
}

TEST_F(forExprTest, returnMiddleOfLoop1) {
    make().parse(R"SRC(
        def person
            name := ""

        main() str
            p1 := person()
            p1.name = "Chales"

            res := (for p in {p1, person()}
                return p1.name
            )
            return res + " Lee"
    )SRC").shouldVerified(true);
    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<std::string>(), "Chales");
}

TEST_F(forExprTest, returnMiddleOfLoop1WithoutParenthesis) {
    make().parse(R"SRC(
        def person
            name := ""

        main() str
            p1 := person()
            p1.name = "Chales"

            res := for p in {p1, person()}
                return p1.name
            return res + " Lee"
    )SRC").shouldVerified(true);
    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<std::string>(), "Chales");
}

TEST_F(forExprTest, retMiddleOfLoop) {
    make().parse(R"SRC(
        def person
            name := ""

        main() str
            p1 := person()
            p1.name = "Chales"

            res := (for p in {p1, person()}
                ret p1.name
            )
            return res + " Lee"
    )SRC").shouldVerified(true);
    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<std::string>(), "Chales Lee");
}

TEST_F(forExprTest, retMiddleOfLoopWithoutParenthesis) {
    make().parse(R"SRC(
        def person
            name := ""

        main() str
            p1 := person()
            p1.name = "Chales"

            res := for p in {p1, person()}
                ret p1.name
            return res + " Lee"
    )SRC").shouldVerified(true);
    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<std::string>(), "Chales Lee");
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
                ret p1.name
            )
            return res
    )SRC").shouldVerified(false);
}

TEST_F(forExprTest, evalForExprWithoutRet) {
    make().parse(R"SRC(
        def person
            name := ""

        main() str
            p1 := person()
            p1.name = "Chales"

            res := (for p in {p1, person()}
                p.name
            )
            return res
    )SRC").shouldVerified(true);
    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<std::string>(), "");
}

TEST_F(forExprTest, simpleBreakTest) {
    make().parse(R"SRC(
        main() int
            res := (for n in 1..10
                break 5
            )
            return res
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
            return res
    )SRC").shouldVerified(true);
    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 5);
}

TEST_F(forExprTest, retForExpr) {
    make().parse(R"SRC(
        main() int
            ret for n in 1..10
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
        main() int
            for n in 1..5
                if n == 3
                    break 7
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
        main() str
            sum := 0
            for n in 0..8
                if sum > 3
                    break "hello"
                ++sum
    )SRC").shouldVerified(true);

    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<std::string>(), "hello");
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
                return

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
                return

        main() int
            sum := 0
            answer := for n in 0..8
                if sum > 11
                    if true
                        break "hello"
                ++sum
    )SRC").shouldVerified(false);
}

TEST_F(forExprTest, evalOfForLoop2) {
    make().negative().parse(R"SRC(
        def a
            foo() void
                return

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

TEST_F(forExprTest, evalOfForLoop3) {
    make().negative().parse(R"SRC(
        main() str
            sum := 0
            answer := for n in 0..8
                if sum > 11
                    if true
                        break "hello"
                ++sum
    )SRC").shouldVerified(true);

    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<std::string>(), "8");
}

