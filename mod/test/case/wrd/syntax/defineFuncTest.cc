#include "../../../syntaxTest.hpp"

using namespace wrd;
using namespace std;

namespace {
    struct defineFuncTest : public syntaxTest {};
}

TEST_F(defineFuncTest, distinguishDefineFuncOrCall) {
    if(make().parse(R"SRC(
        main() void
            foo(a, 22)
    )SRC").expect(true)) {
        node& res = getSubPack();
        ASSERT_FALSE(nul(res));

        const func& f = res.sub<func>("main", narr());
        ASSERT_FALSE(nul(f));
        ASSERT_EQ(f.getName(), "main");
        ASSERT_EQ(f.getParams().len(), 0);
    }
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

TEST_F(defineFuncTest, noBodyNegative) {
    make().parse(R"SRC(
        main() void)SRC").expect(false);

    make().parse(R"SRC(
        main(n int) void
    )SRC").expect(false);
}

TEST_F(defineFuncTest, wrongParamNegative) {
    make().parse(R"SRC(
        main(a) void
            22
    )SRC").expect(false);

    make().parse(R"SRC(
        main(age int()) void
            22
    )SRC").expect(false);

    make().parse(R"SRC(
        main(age + 22, age int) void
            22
    )SRC").expect(false);

    make().parse(R"SRC(
        main(age + 22, age int) void
            22
    )SRC").expect(false);

    make().parse(R"SRC(
        main(aka int -> i) void
            22
    )SRC").expect(false);
}
