#include "../../../wrdSyntaxTest.hpp"

using namespace wrd;
using namespace std;

namespace {
    struct literalTest: public wrdSyntaxTest {};
}

TEST_F(literalTest, stringLiteralShouldFail) {
    make("demo").parse(R"SRC(
        pack demo
        foo(abc int) int
           if "hello"
                       "he
                       ll"
                       if "false"
                               "hel'lo"
    )SRC").shouldParsed(false);
}
