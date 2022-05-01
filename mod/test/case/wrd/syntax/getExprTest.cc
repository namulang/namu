#include "../../../wrdSyntaxTest.hpp"

using namespace wrd;
using namespace std;

namespace {
    struct getExprTest : public wrdSyntaxTest {
    };
}

TEST_F(getExprTest, getSymbolOnPackScope) {
    make().parse(R"SRC(
        main() void
            main
    )SRC").shouldVerified(true);
    ASSERT_EQ(getSubPack().subs().len(), 1); // 1 for main()
}

TEST_F(getExprTest, getSymbolOnPackScope1) {
    // control group.
    make().parse(R"SRC(
        age int
        main() int
            return 0
    )SRC").shouldVerified(true);
    ASSERT_EQ(getSubPack().subs().len(), 2); // 1 for age, 1 for main()
}

TEST_F(getExprTest, getSymbolOnPackScope2) {
    // experimental group.
    make().parse(R"SRC(
        age int
        main() int
            return age
    )SRC").shouldVerified(true);
    ASSERT_EQ(getSubPack().subs().len(), 2); // 1 for age, 1 for main()
}

TEST_F(getExprTest, getSymbolOnPackScope3) {
    make().parse(R"SRC(
        age str
        main() int
            return age
    )SRC").shouldParsed(true);
    shouldVerified(true);
    ASSERT_EQ(getSubPack().subs().len(), 2); // 1 for age, 1 for main()
}

TEST_F(getExprTest, getInnerScopeVar) {
    make().parse(R"SRC(
        age int
        main() int
            age
            age int
            age
    )SRC").shouldVerified(true);
}

TEST_F(getExprTest, getInnerScopeVarNegative) {
    make().parse(R"SRC(
        main() int
            age int
            age
            age int
            age
    )SRC").shouldParsed(true);
    shouldVerified(false);
}
