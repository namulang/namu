#include "../../../namuSyntaxTest.hpp"

using namespace namu;
using namespace std;

namespace {
    struct ifTest : public namuSyntaxTest {};
}

TEST_F(ifTest, simpleNestedTest) {
    make("demo").parse(R"SRC(
        pack demo
        main() void
            if 11
                        22
                        if 22
                                33)SRC").shouldParsed(true);
}

TEST_F(ifTest, NestIfTest) {
    make("demo").parse(R"SRC(
        pack demo
        foo(abc int) int
           if "hello"
                       "hell  '  o"
                       if 33
                               "hel'lo")SRC").shouldParsed(true);
}
