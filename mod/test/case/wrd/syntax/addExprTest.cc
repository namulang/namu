#include "../../../wrdSyntaxTest.hpp"

using namespace wrd;
using namespace std;

namespace {
    struct addExprTest : public wrdSyntaxTest {};
}

TEST_F(addExprTest, simpleAdd) {
    make().parse(R"SRC(
        a := 5
        b := 2
        main() int
            return a + b
    )SRC").shouldVerified(true);

    wInt& a = getSubPack().sub<wInt>("a");
    ASSERT_FALSE(nul(a));
    ASSERT_EQ(a.get(), 5);
    wInt b = getSubPack().sub<wInt>("b");
    ASSERT_EQ(b.get(), 2);

    tstr<wInt> res(getSubPack().run("main"));
    ASSERT_TRUE(res);
    ASSERT_EQ(res->get(), 7);
}

TEST_F(addExprTest, addWithDefAssign) {
    make().parse(R"SRC(
        a := 5
        b := a + 2
        main() int
            return a + b
    )SRC").shouldVerified(true);

    wInt& a = getSubPack().sub<wInt>("a");
    ASSERT_FALSE(nul(a));
    ASSERT_EQ(a.get(), 5);
    wInt b = getSubPack().sub<wInt>("b");
    ASSERT_EQ(b.get(), 7);

    tstr<wInt> res(getSubPack().run("main"));
    ASSERT_TRUE(res);
    ASSERT_EQ(res->get(), 12);
}

TEST_F(addExprTest, addWithDefAssignReversedNegative) {
    make().parse(R"SRC(
        b := a + 2
        a := 5
        main() int
            return a + b
    )SRC").shouldVerified(false);

    wInt& a = getSubPack().sub<wInt>("a");
    ASSERT_FALSE(nul(a));
    ASSERT_EQ(a.get(), 5);
    wInt& b = getSubPack().sub<wInt>("b");
    ASSERT_TRUE(nul(b));
}

TEST_F(addExprTest, addIntAndStrNegative) {
    make().parse(R"SRC(
        a := "hello" + 12
        main() int
            return a
    )SRC").shouldParsed(true);
    shouldVerified(false);
}

TEST_F(addExprTest, addIntAndStr) {
    make().parse(R"SRC(
        a := "hello" + 12
        main() int
            return 0
    )SRC").shouldParsed(true);
    shouldVerified(true);

    wStr& a = getSubPack().sub<wStr>("a");
    ASSERT_FALSE(nul(a));
    ASSERT_EQ(a.get(), std::string("hello12"));
}
