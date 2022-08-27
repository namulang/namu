#include "../../../namuSyntaxTest.hpp"

using namespace namu;
using namespace std;

namespace {
    struct runExprTest : public namuSyntaxTest {};
}

TEST_F(runExprTest, simpleRunCheck) {
    make().parse(R"SRC(
        main() int
            me.main()
            return 0
    )SRC").shouldVerified(true);
}

TEST_F(runExprTest, runWithoutSpecifyingMe) {
    make().parse(R"SRC(
        main() int
            main()
            return 0
    )SRC").shouldVerified(true);
}

TEST_F(runExprTest, runAnotherFunc) {
    make().parse(R"SRC(
        foo() void
            return
        main() void
            foo()
            return
    )SRC").shouldVerified(true);
}

TEST_F(runExprTest, runNotExistFuncNegative) {
    negative().make().parse(R"SRC(
        main() int
            me.foo()
            return 0
    )SRC").shouldParsed(true);
    shouldVerified(false);
}

TEST_F(runExprTest, runAndReturn) {
    make().parse(R"SRC(
        main() int
            main()
    )SRC").shouldVerified(true); // TODO: verify this as warning of infinite reculsive.
}

TEST_F(runExprTest, ArgumentMismatchNegative) {
    negative().make().parse(R"SRC(
        main(str arg) int
            main(3.5)
    )SRC").shouldVerified(false);
}

TEST_F(runExprTest, runAndReturn2) {
    make().parse(R"SRC(
        foo() flt
            return 3.5
        main() flt
            return foo()
    )SRC").shouldVerified(true);
}

TEST_F(runExprTest, runAndReturn3) {
    make().parse(R"SRC(
        foo() flt
            3.5
        main() flt
            foo()
    )SRC").shouldVerified(true);
}

TEST_F(runExprTest, runWithArgument) {
    make().parse(R"SRC(
        foo(age int, grade flt) flt
            return grade
        main() flt
            foo(22, 3.5)
    )SRC").shouldParsed(true);
    shouldVerified(true);
}

TEST_F(runExprTest, runWithArgumentNegative) {
    negative().make().parse(R"SRC(
        foo(name str, grade flt) str
            return name
        main() flt
            foo("hello", 3.5)
    )SRC").shouldParsed(true);
    shouldVerified(false);
}

TEST_F(runExprTest, runWithArgumentNegative2) {
    negative().make().parse(R"SRC(
        foo(name str, grade flt) int
            3
        make() flt
            foo("hello", 3.5)
    )SRC").shouldParsed(true);
    shouldVerified(false);
}
