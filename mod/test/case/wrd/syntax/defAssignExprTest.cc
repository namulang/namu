#include "../../../wrdSyntaxTest.hpp"

using namespace wrd;
using namespace std;

namespace {
    struct defAssignTest : public wrdSyntaxTest {};
}

TEST_F(defAssignTest, simpleGlobalDefAssign) {
    // control group.
    make().parse(R"SRC(
        age int // age is age
        main() int // main is also a main
            age := 5
            return 0
    )SRC").shouldVerified(true);
    ASSERT_EQ(getSubPack().subs().len(), 2); // 1 for age, 1 for main()
    run();
    ASSERT_EQ(getSubPack().sub<wInt>("age").cast<int>(), 0);
}

TEST_F(defAssignTest, simpleLocalDefAssign) {
    // control group.
    make().parse(R"SRC(
        age int // age is age
        main() int // main is also a main
            age = 3
            age := 5
            age = 2
            return 0
    )SRC").shouldVerified(true);
    run();
    ASSERT_EQ(getSubPack().sub("age").cast<int>(), 3);
}
