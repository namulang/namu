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
