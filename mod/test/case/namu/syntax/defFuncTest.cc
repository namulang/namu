#include "../../../namuSyntaxTest.hpp"

using namespace namu;
using namespace std;

namespace {
    struct defFuncTest : public namuSyntaxTest {};
}

TEST_F(defFuncTest, distinguishDefineFuncOrCall) {
    if(make().parse(R"SRC(
        main() void
            foo(a, 22)
    )SRC").shouldParsed(true)) {
        node& res = getSubPack();
        ASSERT_FALSE(nul(res));

        const func& f = res.sub<func>("main", narr());
        ASSERT_FALSE(nul(f));
        ASSERT_EQ(f.getParams().len(), 0);
        ASSERT_EQ(f.getRet().getType(), ttype<wVoid>());
    }

    if(make().parse(R"SRC(
        main(argc int, argv str) void
            foo(a, 22)
    )SRC").shouldParsed(true)) {
        node& res = getSubPack();
        ASSERT_FALSE(nul(res));

        const func& fwrong = res.sub<func>("main", narr());
        ASSERT_TRUE(nul(fwrong));
        const func& f = res.sub<func>("main", narr(wInt(), wStr()));
        ASSERT_FALSE(nul(f));
        ASSERT_EQ(f.getParams().len(), 2);
        ASSERT_EQ(f.getRet().getType(), ttype<wVoid>());

        const params& ps = f.getParams();
        ASSERT_FALSE(nul(ps));
        ASSERT_EQ(ps.len(), 2);

        const param& arg1 = ps[0];
        ASSERT_EQ(arg1.getName(), "argc");
        ASSERT_EQ(arg1.getOrigin().getType(), ttype<wInt>());
        const param& arg2 = ps[1];
        ASSERT_EQ(arg2.getName(), "argv");
        ASSERT_EQ(arg2.getOrigin().getType(), ttype<wStr>());
    }
}

TEST_F(defFuncTest, distinguishDefineFuncOrCall2) {
    make().parse(R"SRC(
        main() void
            foo(a, 22)
                a.doSomething(22)
            foo(a, 22)
    )SRC").shouldParsed(true);
}

TEST_F(defFuncTest, distinguishDefineFuncOrCall3) {
    make().parse(R"SRC(
        main() void
            foo(a, 22)
                a.doSomething(22)
            foo(a, 22)
    )SRC").shouldParsed(true);
}

TEST_F(defFuncTest, distinguishDefineLambdaOrCall) {
    make().parse(R"SRC(
        main() void
            (a, 22) // this is not lambda
    )SRC").shouldParsed(false);
}

TEST_F(defFuncTest, distinguishDefineLambdaOrCall2) {
    make().parse(R"SRC(
        main() void
            (a, 22)
                a.doSomething(22)
            foo(a, 22)
    )SRC").shouldParsed(true);
}

TEST_F(defFuncTest, distinguishDefineLambdaOrCall3) {
    make().parse(R"SRC(
        main() void
            (a, 22)
                a.doSomething(22)
            foo(a, 22))SRC").shouldParsed(true);
}

TEST_F(defFuncTest, lambda1) {
    make().parse(R"SRC(
        main() void
            a.sendPacket((packet)
                doSomething()
            ))SRC").shouldParsed(true);
}

TEST_F(defFuncTest, lambda2) {
    make().parse(R"SRC(
        main() void
            a.sendPacket((packet)
                doSomething()
            ))SRC").shouldParsed(true);
}

TEST_F(defFuncTest, lambda3) {
    make().parse(R"SRC(
        main() void
            a.sendPacket((packet))
            (packet)
            a + 5
    )SRC").shouldParsed(true);
}

TEST_F(defFuncTest, lambda4) {
    make().parse(R"SRC(
        main() void
            a.sendPacket(foo() void
                doSomething()
            ))SRC").shouldParsed(true);
}

TEST_F(defFuncTest, lambda5) {
    make().parse(R"SRC(
        main() void
            a.sendPacket((foo() void
                doSomething()
            ))
    )SRC").shouldParsed(true);
}

TEST_F(defFuncTest, noBodyNegative) {
    make().parse(R"SRC(
        main() void)SRC").shouldParsed(false);

    make().parse(R"SRC(
        main(n int) void
    )SRC").shouldParsed(false);
}

TEST_F(defFuncTest, wrongParamNegative) {
    make().parse(R"SRC(
        main(a) void
            22
    )SRC").shouldParsed(false);

    make().parse(R"SRC(
        main(age int()) void
            22
    )SRC").shouldParsed(false);

    make().parse(R"SRC(
        main(age + 22, age int) void
            22
    )SRC").shouldParsed(false);

    make().parse(R"SRC(
        main(age + 22, age int) void
            22
    )SRC").shouldParsed(false);

    make().parse(R"SRC(
        main(aka int -> i) void
            22
    )SRC").shouldParsed(false);
}

TEST_F(defFuncTest, nameLikeStr) {
    make().parse(R"SRC(
        main(str_ str) str
            return "wow"
    )SRC").shouldParsed(true);
    shouldVerified(true);
}
