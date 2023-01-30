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
