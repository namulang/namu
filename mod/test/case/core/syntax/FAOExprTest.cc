#include "../../../namuSyntaxTest.hpp"

using namespace namu;
using namespace std;

namespace {
    struct FAOExprTest : public namuSyntaxTest {};
}

TEST_F(FAOExprTest, simpleAdd) {
    make().parse(R"SRC(
        b := 2
        main() int
            ret a + b
    )SRC").shouldVerified(true);

    nInt& a = getSubPack().sub<nInt>("a");
    ASSERT_FALSE(nul(a));
    ASSERT_EQ(a.get(), 5);
    nInt b = getSubPack().sub<nInt>("b");
    ASSERT_EQ(b.get(), 2);

    tstr<nInt> res(getSubPack().run("main"));
    ASSERT_TRUE(res);
    ASSERT_EQ(res->get(), 7);
}

TEST_F(FAOExprTest, addWithDefAssign) {
    make().parse(R"SRC(
        foo() int
            1 + 2
        a := 5
        b := a + 2
        main() int
            ret a + b
    )SRC").shouldVerified(true);

    nInt& a = getSubPack().sub<nInt>("a");
    ASSERT_FALSE(nul(a));
    ASSERT_EQ(a.get(), 5);
    nInt b = getSubPack().sub<nInt>("b");
    ASSERT_EQ(b.get(), 7);

    tstr<nInt> res(getSubPack().run("main"));
    ASSERT_TRUE(res);
    ASSERT_EQ(res->get(), 12);
}

TEST_F(FAOExprTest, addWithDefAssignReversedNegative) {
    negative().make().parse(R"SRC(
        b := a + 2
        a := 5
        main() int
            ret a + b
    )SRC").shouldVerified(false);

    nInt& a = getSubPack().sub<nInt>("a");
    ASSERT_FALSE(nul(a));
    ASSERT_EQ(a.get(), 5);
    nInt& b = getSubPack().sub<nInt>("b");
    ASSERT_TRUE(nul(b));
}

TEST_F(FAOExprTest, addIntAndStrNegative) {
    negative().make().parse(R"SRC(
        a := "hello" + 12
    )SRC").shouldParsed(true);
    shouldVerified(false);
}

TEST_F(FAOExprTest, addIntAndStr) {
    make().parse(R"SRC(
        a := "hello" + 12 as str
        main() int
            ret 0
    )SRC").shouldParsed(true);
    shouldVerified(true);

    nStr& a = getSubPack().sub<nStr>("a");
    ASSERT_FALSE(nul(a));
    ASSERT_EQ(a.get(), std::string("hello12"));
}

TEST_F(FAOExprTest, simpleSub) {
    make().parse(R"SRC(
        a := 5
        b := 2
        main() int
            ret a - b
    )SRC").shouldVerified(true);

    nInt& a = getSubPack().sub<nInt>("a");
    ASSERT_FALSE(nul(a));
    ASSERT_EQ(a.get(), 5);
    nInt b = getSubPack().sub<nInt>("b");
    ASSERT_EQ(b.get(), 2);

    tstr<nInt> res(getSubPack().run("main"));
    ASSERT_TRUE(res);
    ASSERT_EQ(res->get(), 3);
}

TEST_F(FAOExprTest, modWithDefAssign) {
    make().parse(R"SRC(
        a := 10
        b := a / 2
        main() int
            ret a * b % 7
    )SRC").shouldVerified(true);

    nInt& a = getSubPack().sub<nInt>("a");
    ASSERT_FALSE(nul(a));
    ASSERT_EQ(a.get(), 10);
    nInt b = getSubPack().sub<nInt>("b");
    ASSERT_EQ(b.get(), 5);

    tstr<nInt> res(getSubPack().run("main"));
    ASSERT_TRUE(res);
    ASSERT_EQ(res->get(), 1);
}

TEST_F(FAOExprTest, testStringAddSequence) {
    make().parse(R"SRC(
    Helloworld(age int) int
        ret age

    main() str
        ret Helloworld(4) as str + "low\n"
    )SRC").shouldVerified(true);

    namu::str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res->cast<std::string>(), "4low\n");
}

TEST_F(FAOExprTest, testStringAddBoolean) {
    make().parse(R"SRC(
    Helloworld(age int) int
        ret age

    main() str
        ret (Helloworld(false as int) as str + "low\n" )
    )SRC").shouldParsed(true);
    shouldVerified(true);


    NAMU_E("start run!");
    namu::str res = run();
    std::string output = res->cast<std::string>();
    ASSERT_EQ(output, "0low\n");
    NAMU_E("end run = %s", output.c_str());
}

TEST_F(FAOExprTest, testStringAddBoolean2) {
    make().parse(R"SRC(
    Helloworld(age int) int
        ret age

    main() str
        ret (Helloworld(false as int) as str + "low\n" )
    )SRC").shouldParsed(true);
    shouldVerified(true);

    namu::str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res->cast<std::string>(), "0low\n");
}

TEST_F(FAOExprTest, testLogicalBinaryOp) {
    make().parse(R"SRC(
        main() bool
            a := 1
            b := 3
            a <= b
    )SRC").shouldVerified(true);

    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nbool>(), true);
}

TEST_F(FAOExprTest, testLogicalBinaryOpWithDifferentType) {
    make().parse(R"SRC(
        main() bool
            a := 1
            b := 3.5
            a > b
    )SRC").shouldVerified(true);

    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nbool>(), false);
}

TEST_F(FAOExprTest, testLogicalBinaryOpFltPrecision) {
    make().parse(R"SRC(
        main() bool
            a := 3.4 + 0.1
            b := 3.5
            a == b
    )SRC").shouldVerified(true);

    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nbool>(), true);
}

TEST_F(FAOExprTest, testLogicalBinaryOpStr) {
    make().parse(R"SRC(
        main() bool
            a := "hello"
            b := "helwo"
            a >= b
    )SRC").shouldVerified(true);

    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nbool>(), false);
}

TEST_F(FAOExprTest, testLogicalBinaryOpChar) {
    make().parse(R"SRC(
        main() bool
            a := 'l'
            b := 'w'
            a > b
    )SRC").shouldVerified(true);

    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nbool>(), false);
}

TEST_F(FAOExprTest, testUnaryPrefixOp) {
    make().parse(R"SRC(
        main() int
            a := 3
            ++a
    )SRC").shouldVerified(true);

    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 4);
}

TEST_F(FAOExprTest, testUnaryPrefixOp2) {
    make().parse(R"SRC(
        main() int
            a := 3
            --a
    )SRC").shouldVerified(true);

    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 2);
}

TEST_F(FAOExprTest, testUnaryPrefixOp3) {
    make().parse(R"SRC(
        main() int
            a := 3
            -a
    )SRC").shouldVerified(true);

    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), -3);
}

TEST_F(FAOExprTest, testUnaryPrefixOp4) {
    make().parse(R"SRC(
        main() int
            a := 3
            if !(a < 3)
                11
            else
                22
    )SRC").shouldVerified(true);

    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 11);
}

TEST_F(FAOExprTest, testUnaryPrefixOp5) {
    make().parse(R"SRC(
        main() int
            a := 3
            if !a
                22
            else
                11
    )SRC").shouldVerified(true);

    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 11);
}

TEST_F(FAOExprTest, testUnaryPrefixOp6) {
    make().parse(R"SRC(
        main() int
            a := 0
            if !a
                22
            else
                11
    )SRC").shouldVerified(true);

    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 22);
}

TEST_F(FAOExprTest, testUnaryPrefixOpNegative) {
    make().negative().parse(R"SRC(
        main() int
            a := "false"
            if !a
                22
            else
                11
    )SRC").shouldParsed(true);
    shouldVerified(false);
}

TEST_F(FAOExprTest, testUnaryPrefixOpNegative2) {
    make().negative().parse(R"SRC(
        main() void
            a := "false"
            ++a
    )SRC").shouldParsed(true);
    shouldVerified(false);
}

TEST_F(FAOExprTest, testUnaryPrefixOpNegative3) {
    make().negative().parse(R"SRC(
        main() void
            a := "false"
            --a
    )SRC").shouldParsed(true);
    shouldVerified(false);
}

TEST_F(FAOExprTest, testStringToBoolean) {
    make().parse(R"SRC(
        main() int
            a := "false"
            if (a as bool) <= 0
                22
            else
                11
    )SRC").shouldVerified(true);

    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 22);
}

TEST_F(FAOExprTest, testStringToBooleanNegative) {
    make().negative().parse(R"SRC(
        main() int
            a := "false"
            if (a as int) <= 0
                22
            else
                11
    )SRC").shouldParsed(true);
    shouldVerified(true);

    // TODO: but runtime exception?
}
