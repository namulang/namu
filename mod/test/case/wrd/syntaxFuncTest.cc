#include "../../syntaxTest.hpp"

using namespace wrd;
using namespace std;

namespace {
    struct syntaxFuncTest : public syntaxTest {};
}

TEST_F(syntaxFuncTest, distinguishDefineFuncOrCall) {
    parse(R"SRC(
main() void
    foo(a, 22)
    )SRC");

    parse(R"SRC(
main() void
    foo(a, 22)
        a.doSomething(22)
    foo(a, 22)
    )SRC");

    parse(R"SRC(
main() void
    foo(a, 22)
        a.doSomething(22)
    foo(a, 22))SRC");
}

TEST_F(syntaxFuncTest, distinguishDefineLambdaOrCall) {
    parse(R"SRC(
main() void
    (a, 22)
    )SRC");

    parse(R"SRC(
main() void
    (a, 22)
        a.doSomething(22)
    foo(a, 22)
    )SRC");

    parse(R"SRC(
main() void
    (a, 22)
        a.doSomething(22)
    foo(a, 22))SRC");
}

TEST_F(syntaxFuncTest, lambda1) {
    parse(R"SRC(
main() void
    a.sendPacket((packet)
        doSomething()
    ))SRC");
}

TEST_F(syntaxFuncTest, lambda2) {
    parse(R"SRC(
main() void
    a.sendPacket((packet)
        doSomething()
    ))SRC");

    parse(R"SRC(
main() void
    a.sendPacket((packet))
    (packet)
    a + 5
    )SRC");
}

TEST_F(syntaxFuncTest, lambda3) {
    parse(R"SRC(
main() void
    a.sendPacket(foo() void
        doSomething()
    ))SRC");
}

TEST_F(syntaxFuncTest, lambda4) {
    parse(R"SRC(
main() void
    a.sendPacket((foo() void
        doSomething()
    )))SRC");
}

