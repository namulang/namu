#include "../../../namuSyntaxTest.hpp"

using namespace namu;
using namespace std;

namespace {
    struct literalExprTest : public namuSyntaxTest {};
}

TEST_F(literalExprTest, hexValue) {
    make().parse(R"SRC(
        main() int
            0xff
    )SRC").shouldVerified(true);

    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 255);
}

TEST_F(literalExprTest, hexValue2) {
    make().parse(R"SRC(
        foo() byte
            0xff
        main() int
            foo()
    )SRC").shouldVerified(true);

    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 255);
}

TEST_F(literalExprTest, octalValue) {
    make().parse(R"SRC(
        main() int
            017
    )SRC").shouldVerified(true);

    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 15);
}

TEST_F(literalExprTest, octalValue2) {
    make().parse(R"SRC(
        foo() byte
            017
        main() int
            foo()
    )SRC").shouldVerified(true);

    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 15);
}
