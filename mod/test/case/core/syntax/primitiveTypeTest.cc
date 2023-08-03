#include "../../../namuSyntaxTest.hpp"

using namespace namu;
using namespace std;

namespace {
    struct primitiveTypeTest: public namuSyntaxTest {};
}

TEST_F(primitiveTypeTest, strFuncLen) {
    make().parse(R"SRC(
        main() int
            word := "hello"
            ret word.len()
    )SRC").shouldVerified(true);

    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), nStr("hello").len());
}

TEST_F(primitiveTypeTest, strFuncGet) {
    make().parse(R"SRC(
        main() int
            "hello"[2] == 'l'
    )SRC").shouldVerified(true);

    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 1);
}

TEST_F(primitiveTypeTest, concatCharAndStr) {
    make().parse(R"SRC(
        main() int
            ("hello" + '1' + "wow" + '2') == "hello1wow2"
    )SRC").shouldVerified(true);

    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 1);
}

TEST_F(primitiveTypeTest, charConversion) {
    make().parse(R"SRC(
        main() int
            a := 'h'
            a as byte == 104
    )SRC").shouldVerified(true);

    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 1);
}

TEST_F(primitiveTypeTest, byteConversion) {
    make().parse(R"SRC(
        main() int
            b := 104
            b as char == 'h'
    )SRC").shouldVerified(true);

    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 1);
}

TEST_F(primitiveTypeTest, strGetSeq) {
    make().parse(R"SRC(
        main() int
            "hello world"[2..4] == "ll"
    )SRC").shouldVerified(true);

    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 1);
}

TEST_F(primitiveTypeTest, strIter) {
    make().parse(R"SRC(
        main() int
            ans := ""
            for c in "hello"
                ans += c
            ret ans == "hello"
    )SRC").shouldVerified(true);

    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 1);
}

TEST_F(primitiveTypeTest, deduceAndImplicitCast) {
    make().parse(R"SRC(
        main() void
            a := 'a' + 1 // a should be char
            print(a)
    )SRC").shouldVerified(true);
}

TEST_F(primitiveTypeTest, deduceAndImplicitCast2) {
    make().parse(R"SRC(
        main() void
            a := 1 + 'a' // a should be char
            print(a)
    )SRC").shouldVerified(true);
}

TEST_F(primitiveTypeTest, strNotSuitableToSomeOpNegative) {
    make().negative().parse(R"SRC(
        main() void
            a := "jokbal"
            a - a
    )SRC").shouldVerified(false);
}

TEST_F(primitiveTypeTest, strNotSuitableToSomeOpNegative2) {
    make().negative().parse(R"SRC(
        main() void
            a := "jokbal"
            a / a
    )SRC").shouldVerified(false);
}

TEST_F(primitiveTypeTest, strNotSuitableToSomeOpNegative3) {
    make().negative().parse(R"SRC(
        main() void
            a := "jokbal"
            a % a
    )SRC").shouldVerified(false);
}

TEST_F(primitiveTypeTest, strNotSuitableToSomeOpNegative4) {
    make().negative().parse(R"SRC(
        main() void
            a := "jokbal"
            a >> 2
    )SRC").shouldVerified(false);
}

TEST_F(primitiveTypeTest, strNotSuitableToSomeOpNegative5) {
    make().negative().parse(R"SRC(
        main() void
            a := "jokbal"
            a & 2
    )SRC").shouldVerified(false);
}
