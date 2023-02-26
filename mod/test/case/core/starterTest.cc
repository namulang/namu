#include "../../namuSyntaxTest.hpp"

using namespace namu;

struct starterTest : public namuSyntaxTest {};

TEST_F(starterTest, simpleStarter) {
    make().parse(R"SRC(
        main() void
            ret
    )SRC");
    shouldVerified(true);

    starter s;
    str res = s.run(args(getSlot().getPack()));
    ASSERT_EQ(*res, nVoid());
}

TEST_F(starterTest, mainReturnInt) {
    make().parse(R"SRC(
        main() int
            ret 23
    )SRC").shouldVerified(true);

    starter s;
    tstr<nInt> res = s.run(args(getSlot().getPack()));
    ASSERT_EQ(res->cast<nInt>().get(), 23);
    ASSERT_EQ(res->cast<int>(), 23);
}

TEST_F(starterTest, mainCallFuncAndCheckReturn) {
    make().parse(R"SRC(
        foo() int
            ret 23
        main() int
            ret foo()
    )SRC").shouldVerified(true);

    starter s;
    tstr<nInt> res = s.run(args(getSlot().getPack()));
    ASSERT_EQ(res->cast<nInt>().get(), 23);
    ASSERT_EQ(res->cast<int>(), 23);
}
