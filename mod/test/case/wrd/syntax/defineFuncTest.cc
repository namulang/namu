#include "../../../syntaxTest.hpp"

using namespace wrd;
using namespace std;

namespace {
    struct defineFuncTest : public syntaxTest {};
}

TEST_F(defineFuncTest, distinguishDefineFuncOrCall) {
    make().parse(R"SRC(
        main() void
            foo(a, 22)
    )SRC").expect(true);
}

TEST_F(defineFuncTest, distinguishDefineFuncOrCall2) {
    make().parse(R"SRC(
        main() void
            foo(a, 22)
                a.doSomething(22)
            foo(a, 22)
    )SRC").expect(true);
}

TEST_F(defineFuncTest, distinguishDefineFuncOrCall3) {
    make().parse(R"SRC(
        main() void
            foo(a, 22)
                a.doSomething(22)
            foo(a, 22)
    )SRC").expect(true);
}

TEST_F(defineFuncTest, distinguishDefineLambdaOrCall) {
    make().parse(R"SRC(
        main() void
            (a, 22)
    )SRC").expect(true);
}

TEST_F(defineFuncTest, distinguishDefineLambdaOrCall2) {
    make().parse(R"SRC(
        main() void
            (a, 22)
                a.doSomething(22)
            foo(a, 22)
    )SRC").expect(true);
}

TEST_F(defineFuncTest, distinguishDefineLambdaOrCall3) {
    make().parse(R"SRC(
        main() void
            (a, 22)
                a.doSomething(22)
            foo(a, 22))SRC").expect(true);
}

TEST_F(defineFuncTest, lambda1) {
    make().parse(R"SRC(
        main() void
            a.sendPacket((packet)
                doSomething()
            ))SRC").expect(true);
}

TEST_F(defineFuncTest, lambda2) {
    make().parse(R"SRC(
        main() void
            a.sendPacket((packet)
                doSomething()
            ))SRC").expect(true);
}

TEST_F(defineFuncTest, lambda3) {
    make().parse(R"SRC(
        main() void
            a.sendPacket((packet))
            (packet)
            a + 5
    )SRC").expect(true);
}

TEST_F(defineFuncTest, lambda4) {
    make().parse(R"SRC(
        main() void
            a.sendPacket(foo() void
                doSomething()
            ))SRC").expect(true);
}

TEST_F(defineFuncTest, lambda5) {
    make().parse(R"SRC(
        main() void
            a.sendPacket((foo() void
                doSomething()
            ))
    )SRC").expect(true);
}

