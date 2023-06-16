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
