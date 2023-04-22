#include "../../../namuSyntaxTest.hpp"

using namespace namu;
using namespace std;

namespace {
    struct commentTest : public namuSyntaxTest {};
}

TEST_F(commentTest, singleLineComment) {
    // control group.
    make().parse(R"SRC(
        age int // age is age
        main() int // main is also a main
            ret 0
    )SRC").shouldVerified(true);

    scope& owns = (scope&) (((scopes&) getSlot().subs()).getContainer());
    scope& shares = (scope&) (((scopes&) getSubPack().subs()).getNext().getContainer());
    ASSERT_FALSE(nul(shares));
    ASSERT_FALSE(nul(owns));
    ASSERT_EQ(owns.len(), 1); // 1 for age
    ASSERT_EQ(shares.len(), 3); // 1 for main() 2 for @ctor
}

TEST_F(commentTest, multiLineComment) {
    // control group.
    make().parse(R"SRC(
        age int /* age is age
        main() int */
        main() flt
            ret 2.5
    )SRC").shouldVerified(true);
    scope& owns = (scope&) (((scopes&) getSlot().subs()).getContainer());
    scope& shares = (scope&) (((scopes&) getSubPack().subs()).getNext().getContainer());
    ASSERT_FALSE(nul(shares));
    ASSERT_FALSE(nul(owns));
    ASSERT_EQ(owns.len(), 1); // 1 for age
    ASSERT_EQ(shares.len(), 3); // 1 for main() 2 for @ctor
}

TEST_F(commentTest, multiLineComment2) {
    // control group.
    make().parse(R"SRC(
        age /* age is age
        main() int
 sdfas   */int
        main() void
            ret
    )SRC").shouldVerified(true);
    scope& owns = (scope&) (((scopes&) getSlot().subs()).getContainer());
    scope& shares = (scope&) (((scopes&) getSubPack().subs()).getNext().getContainer());
    ASSERT_FALSE(nul(shares));
    ASSERT_FALSE(nul(owns));
    ASSERT_EQ(owns.len(), 1); // 1 for age
    ASSERT_EQ(shares.len(), 3); // 1 for main() 2 for @ctor
}

TEST_F(commentTest, multiLineComment3) {
    // control group.
    make().parse(R"SRC(
        age int /* age is age
        main() int
 sdfas*/main() int
            ret 33
    )SRC").shouldParsed(false);
/* above case is same to,
 *
 *      age int main() bool
 *          ret false
 */
}
