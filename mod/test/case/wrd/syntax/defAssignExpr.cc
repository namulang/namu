#include "../../../wrdSyntaxTest.hpp"

using namespace wrd;
using namespace std;

namespace {
    struct defAssignTest : public wrdSyntaxTest {};
}

TEST_F(defAssignTest, singleLineComment) {
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
