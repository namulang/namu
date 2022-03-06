#include "../../../syntaxTest.hpp"

using namespace wrd;
using namespace std;

namespace {
    struct literalTest: public syntaxTest {};
}

TEST_F(literalTest, stringLiteralShouldFail) {
    make().parse(R"SRC(
        pack demo
        foo(abc int) int
           if "hello"
                       "he
                       ll"
                       if "false"
                               "hel'lo"
    )SRC").shouldParsed(false);
}
