#include "../../../namuSyntaxTest.hpp"

using namespace namu;
using namespace std;

namespace {
    struct FBOExprTest : public namuSyntaxTest {};
}

TEST_F(FBOExprTest, simpleAdd) {
    make().parse(R"SRC(
        a := 5
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

TEST_F(FBOExprTest, addWithDefAssign) {
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

TEST_F(FBOExprTest, addWithDefAssignReversedNegative) {
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

TEST_F(FBOExprTest, addIntAndStrNegative) {
    negative().make().parse(R"SRC(
        a := "hello" + 12
    )SRC").shouldParsed(true);
    shouldVerified(false);
}

TEST_F(FBOExprTest, addIntAndStr) {
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

TEST_F(FBOExprTest, simpleSub) {
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

TEST_F(FBOExprTest, modWithDefAssign) {
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

TEST_F(FBOExprTest, testStringAddSequence) {
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

TEST_F(FBOExprTest, testStringAddBoolean) {
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

TEST_F(FBOExprTest, testStringAddBoolean2) {
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

TEST_F(FBOExprTest, testLogicalBinaryOp) {
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

TEST_F(FBOExprTest, testLogicalBinaryOpWithDifferentType) {
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

TEST_F(FBOExprTest, testLogicalBinaryOpFltPrecision) {
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

TEST_F(FBOExprTest, testLogicalBinaryOpStr) {
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

TEST_F(FBOExprTest, testLogicalBinaryOpChar) {
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

TEST_F(FBOExprTest, testStringToBoolean) {
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

TEST_F(FBOExprTest, testStringToBooleanNegative) {
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

TEST_F(FBOExprTest, testLogicalAndOp) {
    make().parse(R"SRC(
        main() bool
            ret true && 3 < 27
    )SRC").shouldVerified(true);

    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nbool>(), true);
}

TEST_F(FBOExprTest, testLogicalAndOpNegative) {
    make().negative().parse(R"SRC(
        foo() bool
            false

        main() bool
            a := 0
            if (foo() && a = 1)
                sys.con.print("ok")
            ret a
    )SRC").shouldVerified(false);
}

TEST_F(FBOExprTest, testLogicalAndOp2) {
    make().parse(R"SRC(
        foo() bool
            false

        main() bool
            a := 0
            if (foo() && (a = 1))
                sys.con.print("ok")
            ret a
    )SRC").shouldVerified(true);

    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res->getType(), ttype<nBool>::get());
    ASSERT_EQ(res.cast<nbool>(), true);
}

TEST_F(FBOExprTest, testLogicalAndOpShortCircuit) {
    make().parse(R"SRC(
        main() int
            if true || false
                sys.con.print("ok")
            ret 0
    )SRC");

    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res->getType(), ttype<nInt>::get());
    ASSERT_EQ(res.cast<nint>(), 0);
}
