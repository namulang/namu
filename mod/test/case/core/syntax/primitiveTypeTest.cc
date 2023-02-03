#include "../../../namuSyntaxTest.hpp"

using namespace namu;
using namespace std;

namespace {
    struct primitiveTypeTest: public namuSyntaxTest {};
}

TEST_F(primitiveTypeTest, strFuncs) {
    make().parse(R"SRC(
        main() int
            word := "hello"
            return word.len()
    )SRC").shouldVerified(true);

    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), nStr("hello").len());
}
