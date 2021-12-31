#include "../syntaxTest.hpp"

using namespace wrd;
using namespace std;

namespace {
    struct syntaxExprTest : public syntaxTest {};
}

TEST_F(syntaxExprTest, exprTest) {
    parse(R"SRC(
pack demo
main() void
    if 11
                22
                if 22
                        33)SRC");
}

TEST_F(syntaxExprTest, exprTest1) {
    parse(R"SRC(
 pack demo
 foo(abc int) int
    if "hello"
                'hell  "  o'
                if 33
                        "hel'lo")SRC");
}

TEST_F(syntaxExprTest, stringLiteralShouldFail) {
    parseFail(R"SRC(
 pack demo
 foo(abc int) int
    if 'hello'
                'he
                ll'
                if 'false'
                        "hel'lo")SRC");
}

TEST_F(syntaxExprTest, exprTest3) {
    parse(R"SRC(
 pack demo
 main() void
    if 'good'
      2 + 3*27 + 44 - 27/34*43 - 1
    )SRC");
}

TEST_F(syntaxExprTest, exprTest4) {
    parse(R"SRC(
 pack demo
 main() void
    if 'good'
      2 + (if 3
       3*27
      )+ 44 - 27/34*43 - 1
    )SRC");
    parseFail(R"SRC(
 pack demo
 main() void
    if 'good'
      2 + (if 3
       3*27)+ 44 - 27/34*43 - 1
    )SRC");
    parseFail(R"SRC(
 pack demo
 main() void
    if 'good'
      2 + if 3
       3*27
      + 44 - 27/34*43 - 1
    )SRC");
}

TEST_F(syntaxExprTest, callFunc) {
    parse(R"SRC(
pack demo
main() void
    if 'wow'
        foo()
    )SRC");

    parse(R"SRC(
main() void
    if 'wow'
        a.foo()
    )SRC");

    parse(R"SRC(
main() void
    if 'wow'
        --a++.foo()
    )SRC");

    parse(R"SRC(
main() void
    if 'wow'
        (--a++.foo()).doo().goo()
    )SRC");
}

/*TEST_F(syntaxExprTest, testParseHelloWorld) {
    parse(R"SRC(
        main() void
            out('hello world!')
    )SRC"); // this code can't be run, but can be parsed.
}

TEST_F(syntaxExprTest, testHelloWorld) {
    auto unit = parse(R"SRC(
    parse(R"SRC(
        import cons

        main() void
            cons.out('hello world!')
    )SRC");
    ASSERT_FALSE(nul(unit));
    //TODO: const char* expectOut = "hello world!";
}*/
