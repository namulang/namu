#include "../../../namuSyntaxTest.hpp"

using namespace namu;
using namespace std;

namespace {
    struct whileExprTest : public namuSyntaxTest {};
}

TEST_F(whileExprTest, simple) {
    make().parse(R"SRC(
        main() int
            sum := 0
            n := 0
            while n <= 3
                sum = sum + n
                n = n + 1
                sys.con.print("sum=" + sum + ", n=" + n + "\n")
            return sum
    )SRC").shouldVerified(true);
    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 6);
}

TEST_F(whileExprTest, conditionClauseCheckNegative) {
    make().negative().parse(R"SRC(
        main() int
            sum := 0
            n := 0
            while n <= foo()
                sum = sum + n
                n = n + 1
                sys.con.print("sum=" + sum + ", n=" + n + "\n")
            return sum
    )SRC").shouldVerified(false);
}

TEST_F(whileExprTest, conditionClauseCheck) {
    make().parse(R"SRC(
        foo() int
            return 3

        main() int
            sum := 0
            n := 0
            while n <= foo()
                sum = sum + n
                n = n + 1
                sys.con.print("sum=" + sum + ", n=" + n + "\n")
            return sum
    )SRC").shouldVerified(true);

    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 6);
}

TEST_F(whileExprTest, breakInsideOfFor) {
    make().parse(R"SRC(
        main() int
            n := 0
            while n < 5
                break 7
    )SRC").shouldVerified(true);

    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 7);
}

TEST_F(whileExprTest, breakInsideOfIfExpr) {
    make().parse(R"SRC(
        main() int
            n := 0
            while n < 5
                if ++n == 3
                    break 7
    )SRC").shouldVerified(true);

    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 7);
}

TEST_F(whileExprTest, breakNestedForLoop) {
    make().parse(R"SRC(
        main() int
            sum := 0
            n := 0
            n2 := 0

            while ++n < 8
                while ++n2 < 4
                    ++sum
                    if sum > 15
                        break
                n2 = 0
                if sum > 15
                    break
            sum
    )SRC").shouldVerified(true);

    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 16);
}

TEST_F(whileExprTest, evalOfForLoop) {
    make().parse(R"SRC(
        main() str
            sum := 0
            n := 0
            while ++n < 8
                if sum > 3
                    break "hello"
                ++sum
    )SRC").shouldVerified(true);

    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<std::string>(), "hello");
}

TEST_F(whileExprTest, evalOfForLoopNegative) {
    make().negative().parse(R"SRC(
        main() int
            sum := 0
            n := 0
            while ++n < 8
                if sum > 3
                    break "hello"
                ++sum
    )SRC").shouldVerified(false);
}

TEST_F(whileExprTest, evalOfForLoopNegative2) {
    make().negative().parse(R"SRC(
        def a
            foo() void
                return

        main() int
            sum := 0
            n := 0
            while ++n < 8
                if sum > 3
                    break a()
                ++sum
    )SRC").shouldVerified(false);
}

TEST_F(whileExprTest, evalOfForLoop2) {
    make().negative().parse(R"SRC(
        def a
            foo() void
                return

        main() int
            sum := 0
            n := 0
            while ++n < 8
                if sum > 3
                    break a()
                ++sum
            sum
    )SRC").shouldVerified(true);

    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 4);
}
