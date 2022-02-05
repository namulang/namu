#include "../../syntaxTest.hpp"

using namespace wrd;
using namespace std;

namespace {
    struct syntaxExprTest : public syntaxTest {};
}

TEST_F(syntaxExprTest, exprTest) {
    make().parse(R"SRC(
pack demo
main() void
    if 11
                22
                if 22
                        33)SRC").expect(true);
}

TEST_F(syntaxExprTest, exprTest1) {
    make().parse(R"SRC(
 pack demo
 foo(abc int) int
    if "hello"
                "hell  '  o"
                if 33
                        "hel'lo")SRC").expect(true);
}

TEST_F(syntaxExprTest, stringLiteralShouldFail) {
    make().parse(R"SRC(
 pack demo
 foo(abc int) int
    if "hello"
                "he
                ll"
                if "false"
                        "hel'lo")SRC").expect(false);
}

TEST_F(syntaxExprTest, exprTest3) {
    make().parse(R"SRC(
 pack demo
 main() void
    if "good"
      2 + 3*27 + 44 - 27/34*43 - 1
    )SRC").expect(true);
}

TEST_F(syntaxExprTest, exprTest4) {
    make().parse(R"SRC(
 pack demo
 main() void
    if "good"
      2 + (if 3
       3*27
      )+ 44 - 27/34*43 - 1
    )SRC").expect(true);
    make().parse(R"SRC(
 pack demo
 main() void
    if "good"
      2 + (if 3
       3*27)+ 44 - 27/34*43 - 1
    )SRC").expect(false);
    make().parse(R"SRC(
 pack demo
 main() void
    if "good"
      2 + if 3
       3*27
      + 44 - 27/34*43 - 1
    )SRC").expect(false);
}

TEST_F(syntaxExprTest, defexprAsTerm) {
    make().parse(R"SRC(
 pack demo
 main() void
    if "good"
      (age int) + (if 3
       3*27
      ) + (grade flt) - 27/34*43 - 1
    )SRC").expect(true);
}

TEST_F(syntaxExprTest, exprAddFuncCall) {
    make().parse(R"SRC(
 pack demo
 main() void
    if "good"
      2 + 3*27 + 44 - foo(2) * 27/34*43
    )SRC").expect(true);
}

TEST_F(syntaxExprTest, exprAddFuncCall2) {
    make().parse(R"SRC(
 pack demo
 main() void
    if "good"
      2 + 3*27 + 44 - foo('a') * 27/34*43 - a.foo(b.boo(c.goo()))
    )SRC").expect(true);

    make().parse(R"SRC(
 pack demo
 main() void
    if "good"
      2 + 3*27 + 44 - foo('a12') * 27/34*43 - a.foo(b.boo(c.goo()))
    )SRC").expect(false);
}

TEST_F(syntaxExprTest, callFunc) {
    make().parse(R"SRC(
pack demo
main() void
    if "wow"
        foo()
    )SRC").expect(true);

    make().parse(R"SRC(
main() void
    if "wow"
        a.foo()
    )SRC").expect(true);

    make().parse(R"SRC(
main() void
    if "wow"
        --a++.foo()
    )SRC").expect(true);

    make().parse(R"SRC(
main() void
    if "wow"
        (--a++.foo()).doo().goo()
    )SRC").expect(true);
}

TEST_F(syntaxExprTest, callFuncWithExprInside) {
    make().parse(R"SRC(
main() void
    if "test"
        a.foo(22, 34)
    )SRC").expect(true);
}

TEST_F(syntaxExprTest, callFuncWithExprInside1) {
    make().parse(R"SRC(
main() void
    if "test"
        a.foo(22, 34, boo(22))
    )SRC").expect(true);
}

TEST_F(syntaxExprTest, callFuncWithExprInside2) {
    make().parse(R"SRC(
main() void
    if "test"
        a.foo(22, 34, boo(a int) void
            b.boo(a)
        )
    )SRC").expect(true);

    make().parse(R"SRC(
main() void
    if "test"
        a.foo(22, 34, (boo(a int) void
            b.boo(a)
        ))
    )SRC").expect(true);
}

TEST_F(syntaxExprTest, IgnoreWhitespaceOnBinaryOperator) {
    make().parse(R"SRC(
main() void
    2 +
        3)SRC").expect(true);
}
TEST_F(syntaxExprTest, IgnoreWhitespaceOnBinaryOperator1) {
    make().parse(R"SRC(
main() void
    activateFrame(ContextManager,
    view.update(context),
    22,
    34) + 2 +
        3)SRC").expect(true);
}
TEST_F(syntaxExprTest, IgnoreWhitespaceOnBinaryOperator2) {
    make().parse(R"SRC(
main() void
    activateFrame(ContextManager,
        view.update(context),
22,
                    34) + 2 +
        3)SRC").expect(true);
}
TEST_F(syntaxExprTest, IgnoreWhitespaceOnBinaryOperator3) {
    make().parse(R"SRC(
main() void
    activateFrame(
     ContextManager,
       view.update(
        context),
22,
                    34) +
                     2 +
        3)SRC").expect(true);
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
