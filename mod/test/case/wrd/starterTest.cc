#include "../../wrdSyntaxTest.hpp"

using namespace wrd;

struct starterTest : public wrdSyntaxTest {};

TEST_F(starterTest, simpleStarter) {
	make().parse(R"SRC(
		main() void
			return
	)SRC");
	shouldVerified(true);

    starter s;
    str res = s.run(narr(getPack()));
    ASSERT_EQ(*res, wVoid());
}

TEST_F(starterTest, mainReturnInt) {
    make().parse(R"SRC(
        main() int
            return 23
    )SRC").shouldVerified(true);

    starter s;
    tstr<wInt> res = s.run(narr(getPack()));
    ASSERT_EQ(res->cast<wInt>().get(), 23);
    ASSERT_EQ(res->cast<int>(), 23);
}

TEST_F(starterTest, mainCallFuncAndCheckReturn) {
    make().parse(R"SRC(
        foo() int
            return 23
        main() int
            return foo()
    )SRC").shouldVerified(true);

    starter s;
    tstr<wInt> res = s.run(narr(getPack()));
    ASSERT_EQ(res->cast<wInt>().get(), 23);
    ASSERT_EQ(res->cast<int>(), 23);
}
