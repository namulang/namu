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

TEST_F(stmtChainTest, chain4) {
    make().negative().parse(R"SRC(
        main() void
            for n in 2..5: foo(3); if true: return
    )SRC").shouldParsed(true);
}

TEST_F(stmtChainTest, chainNegative1) {
    make().negative().parse(R"SRC(
        main() void
            for n in 2..5: foo(3); if true: foo(5); print("this is inside of if expr")
                return // invalid syntax: when you define block as inline, it should be ended in one line.
                       // so next line can't be part of the block.
    )SRC").shouldParsed(true);
}

TEST_F(stmtChainTest, chain5) {
    make().negative().parse(R"SRC(
        main() void
            for n in 2..5: foo(3); if true: foo(5); print("this is inside of if expr")
            return // ok. belonged to 'main()' func.
    )SRC").shouldParsed(true);
}
