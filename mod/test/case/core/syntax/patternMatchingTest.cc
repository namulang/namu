#include "../../../namuSyntaxTest.hpp"

using namespace namu;

namespace {
    struct patternMatchingTest: public namuSyntaxTest {};
}

TEST_F(patternMatchingTest, simpleIn) {
    make().parse(R"SRC(
        main() int
            arr := {1, 2, 3}
            3 in arr
    )SRC").shouldVerified(true);

    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res->cast<nint>(), 1);
}

TEST_F(patternMatchingTest, simpleInWithStrNegative) {
    make().parse(R"SRC(
        main() int
            arr := {"1", "2", "3"}
            "hello" in arr
    )SRC").shouldVerified(true);

    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res->cast<nint>(), 0);
}

TEST_F(patternMatchingTest, simpleInWithStr) {
    make().parse(R"SRC(
        main() int
            arr := {"1", "2", "3"}
            "2" in arr
    )SRC").shouldVerified(true);

    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res->cast<nint>(), 1);
}
