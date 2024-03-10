#include "../../../namuSyntaxTest.hpp"

using namespace namu;

namespace {
    struct stmtChainTest : public namuSyntaxTest {};
}

TEST_F(stmtChainTest, simpleChain) {
    make().negative().parse(R"SRC(
        age := for n in 2..5: n
    )SRC").shouldParsed(true);
}

TEST_F(stmtChainTest, chain2) {
    make().negative().parse(R"SRC(
        main() void
            for n in 2..5: foo(3); boo(3)
    )SRC").shouldParsed(true);
}

TEST_F(stmtChainTest, chain3) {
    make().negative().parse(R"SRC(
        main() void
            for n in 2..5: foo(3); age := 2 + 5
    )SRC").shouldParsed(true);
}
