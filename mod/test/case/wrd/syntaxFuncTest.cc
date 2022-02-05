#include "../../syntaxTest.hpp"

using namespace wrd;
using namespace std;

namespace {
    struct syntaxFuncTest : public syntaxTest {};
}

TEST_F(syntaxFuncTest, distinguishDefineFuncOrCall) {
    make().parse(R"SRC(
main() void
    foo(a, 22)
    )SRC").expect(true);

    make().parse(R"SRC(
main() void
    foo(a, 22)
        a.doSomething(22)
    foo(a, 22)
    )SRC").expect(true);

    make().parse(R"SRC(
main() void
    foo(a, 22)
        a.doSomething(22)
    foo(a, 22))SRC").expect(true);
}

TEST_F(syntaxFuncTest, distinguishDefineLambdaOrCall) {
    make().parse(R"SRC(
main() void
    (a, 22)
    )SRC").expect(true);

    make().parse(R"SRC(
main() void
    (a, 22)
        a.doSomething(22)
    foo(a, 22)
    )SRC").expect(true);

    make().parse(R"SRC(
main() void
    (a, 22)
        a.doSomething(22)
    foo(a, 22))SRC").expect(true);
}

TEST_F(syntaxFuncTest, lambda1) {
    make().parse(R"SRC(
main() void
    a.sendPacket((packet)
        doSomething()
    ))SRC").expect(true);
}

TEST_F(syntaxFuncTest, lambda2) {
    make().parse(R"SRC(
main() void
    a.sendPacket((packet)
        doSomething()
    ))SRC").expect(true);

    make().parse(R"SRC(
main() void
    a.sendPacket((packet))
    (packet)
    a + 5
    )SRC").expect(true);
}

TEST_F(syntaxFuncTest, lambda3) {
    make().parse(R"SRC(
main() void
    a.sendPacket(foo() void
        doSomething()
    ))SRC").expect(true);
}

TEST_F(syntaxFuncTest, lambda4) {
    make().parse(R"SRC(
main() void
    a.sendPacket((foo() void
        doSomething()
    )))SRC").expect(true);
}

