#include "../../../namuSyntaxTest.hpp"

using namespace namu;
using namespace std;

namespace {
    struct assignExprTest : public namuSyntaxTest {};
}

TEST_F(assignExprTest, simpleAssignPositive) {
    if(make().parse(R"SRC(
        age int
        main() int
            age = 5 // return age implicitly
    )SRC").shouldVerified(true)) {
        run();
        node& res = getSubPack();
        ASSERT_FALSE(nul(res));

        const nInt& o = res.sub<nInt>("age");
        ASSERT_FALSE(nul(o));
        ASSERT_EQ(o.cast<nint>(), 5);
    }
}

TEST_F(assignExprTest, simpleAssignReturn) {
    make().parse(R"SRC(
        age int
        main() void
            age = 5
    )SRC").shouldVerified(true);
}

TEST_F(assignExprTest, assignLocalVariable) {
    if(make().parse(R"SRC(
        age int
        main() int
            age = 5

            age int
            return age = 3
    )SRC").shouldVerified(true)) {
        run();
        node& res = getSubPack();
        ASSERT_FALSE(nul(res));

        const nInt& o = res.sub<nInt>("age");
        ASSERT_FALSE(nul(o));
        ASSERT_EQ(o.cast<int>(), 5);
    }
}

TEST_F(assignExprTest, assignTypeNegative) {
    make().parse(R"SRC(
        age int
        main() int
            return age = "wow"
    )SRC").shouldParsed(true);
    shouldVerified(false);
}

TEST_F(assignExprTest, mysteriousDeath) {
    make().parse(R"SRC(
        age := 0
        main() int
            return age = age + 1
    )SRC").shouldVerified(true);
    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<int>(), 1);
}

// TODO: assignNegative inheritence
// TODO: assignDotChain: A.B.name
// TODO: assignComplexDotChain: B[A.foo() + 3].name
