#include "../../../wrdSyntaxTest.hpp"

using namespace wrd;
using namespace std;

namespace {
    struct getExprTest : public wrdSyntaxTest {
    };
}

TEST_F(getExprTest, getSymbolOnPackScope) {
    make().parse(R"SRC(
        main() void
            main
    )SRC").shouldVerified(true);

    // control group.
    make().parse(R"SRC(
        age int
        main() int
            return 0
    )SRC").shouldVerified(true);

    // experimental group.
    make().parse(R"SRC(
        age int
        main() int
            return age
    )SRC").shouldVerified(true);
    make().parse(R"SRC(
        age str
        main() int
            return age
    )SRC").shouldParsed(true);
    shouldVerified(false);
}

TEST_F(getExprTest, getInnerScopeVar) {
    make().parse(R"SRC(
        age int
        main() int
            age
            age int
            age
    )SRC").shouldVerified(true);
}

TEST_F(getExprTest, getInnerScopeVarNegative) {
    make().parse(R"SRC(
        main() int
            age int
            age
            age int
            age
    )SRC").shouldParsed(true);
    shouldVerified(false);
}
