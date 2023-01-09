#include "../../../namuSyntaxTest.hpp"

using namespace namu;
using namespace std;

namespace {
    struct ifTest : public namuSyntaxTest {};
}

TEST_F(ifTest, simpleNestedTest) {
    make("demo").parse(R"SRC(
        pack demo
        main() void
            if 11
                        22
                        if 22
                                33)SRC").shouldVerified(true);
}

TEST_F(ifTest, simpleIfTest) {
    make().parse(R"SRC(
        main() int
            if true
                return 11
            else
                return 22
    )SRC").shouldVerified(true);
    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 11);
}

TEST_F(ifTest, simpleIfAssignTest) {
    make().parse(R"SRC(
        main() int
            age := (if false
                11
            else
                22
            )
            return age
    )SRC").shouldVerified(true);
    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 22);
}

TEST_F(ifTest, simpleIfAssignWithoutParenthesisTest) {
    make().parse(R"SRC(
        main() int
            age := if false
                11
            else
                22
            return age
    )SRC").shouldVerified(true);
    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 22);
}

TEST_F(ifTest, simpleReturnIfWithoutParenthesisTest) {
    make().parse(R"SRC(
        main() int
            return if true
                11
            else
                22
    )SRC").shouldVerified(true);
    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 11);
}

TEST_F(ifTest, simpleReturnDefAssignWithoutParenthesisTest) {
    make().parse(R"SRC(
        main() int
            return a := if true
                11
            else
                22
    )SRC").shouldVerified(true);
    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 11);
}

TEST_F(ifTest, NestIfTest) {
    make("demo").parse(R"SRC(
        pack demo
        foo(abc int) void
           if "hello"
                       "hell  '  o"
                       if 33
                               "hel'lo")SRC").shouldVerified(true);
}

TEST_F(ifTest, NestIfTestNegative) {
    make("demo").negative().parse(R"SRC(
        pack demo
        foo(abc int) int
           if "hello"
                       "hell  '  o"
                       if 33
                               "hel'lo")SRC").shouldVerified(false);
}

TEST_F(ifTest, ifAsArgument) {
    make().parse(R"SRC(
        abc(val int, val2 int) int
            return val + val2

        main() int
            abc(if false
                22
            else
                11
            , 5)
    )SRC").shouldVerified(true);
    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 27);
}
