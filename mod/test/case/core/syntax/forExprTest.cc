#include "../../../namuSyntaxTest.hpp"

using namespace namu;
using namespace std;

namespace {
    struct forTest : public namuSyntaxTest {};
}

TEST_F(forTest, simpleTest) {
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

TEST_F(forTest, simpleTest2) {
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

TEST_F(forTest, testWhatFromFunc) {
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
