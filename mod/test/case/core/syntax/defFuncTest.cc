#include "../../../namuSyntaxTest.hpp"

using namespace namu;
using namespace std;

namespace {
    struct defFuncTest : public namuSyntaxTest {};
}

TEST_F(defFuncTest, distinguishDefineFuncOrCall) {
    if(make().parse(R"SRC(
        foo(x int, y int) void
            ret

        main() void
            a := 22
            foo(a, 22)
    )SRC").shouldParsed(true)) {
        node& res = getSubPack();
        ASSERT_FALSE(nul(res));

        const func& f = res.sub<func>("main", narr());
        ASSERT_FALSE(nul(f));
        ASSERT_EQ(f.getParams().len(), 0);
        ASSERT_EQ(f.getRet()->getType(), ttype<nVoid>());
    }

    if(make().parse(R"SRC(
        foo(x int, y int) void
            ret

        main(argc int, argv str) void
            foo(argc, 22)
    )SRC").shouldParsed(true)) {
        node& res = getSubPack();
        ASSERT_FALSE(nul(res));

        const func& fwrong = res.sub<func>("main", narr());
        ASSERT_TRUE(nul(fwrong));
        const func& f = res.sub<func>("main", narr(nInt(), nStr()));
        ASSERT_FALSE(nul(f));
        ASSERT_EQ(f.getParams().len(), 2);
        ASSERT_EQ(f.getRet()->getType(), ttype<nVoid>());

        const params& ps = f.getParams();
        ASSERT_FALSE(nul(ps));
        ASSERT_EQ(ps.len(), 2);

        const param& arg1 = ps[0];
        ASSERT_EQ(arg1.getName(), "argc");
        ASSERT_EQ(arg1.getOrigin().getType(), ttype<nInt>());
        const param& arg2 = ps[1];
        ASSERT_EQ(arg2.getName(), "argv");
        ASSERT_EQ(arg2.getOrigin().getType(), ttype<nStr>());
    }
}

TEST_F(defFuncTest, distinguishDefineFuncOrCall2) {
    make().negative().parse(R"SRC(
        main() void
            foo(a, 22)
                a.doSomething(22)
            foo(a, 22)
    )SRC").shouldParsed(true);
    shouldVerified(false);
}

TEST_F(defFuncTest, distinguishDefineFuncOrCall3) {
    make().negative().parse(R"SRC(
        main() void
            foo(a, 22)
                a.doSomething(22)
            foo(a, 22)
    )SRC").shouldParsed(true);
    shouldVerified(false);
}

TEST_F(defFuncTest, distinguishDefineLambdaOrCall) {
    make().negative().parse(R"SRC(
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
    negative().make().parse(R"SRC(
        main() void)SRC").shouldParsed(false);

    make().parse(R"SRC(
        main(n int) void
    )SRC").shouldParsed(false);
}

TEST_F(defFuncTest, wrongParamNegative) {
    negative().make().parse(R"SRC(
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
        main(str_ str) int
            ret "wow".len()
    )SRC").shouldParsed(true);
    shouldVerified(true);
}

TEST_F(defFuncTest, defFuncAtSubPack) {
    make().parse(R"SRC(
        foo(msg str[]) str
            print(msg[0])
            msg[0]

        main() int
            msgs := {"hello", "world"}
            foo(msgs) == "hello"
    )SRC").shouldVerified(true);
    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 1);
}

TEST_F(defFuncTest, defFuncReturnClass) {
    make().parse(R"SRC(
        foo() A
            A()
        def A
            age := 0
        main() int
            a := 'r'
            foo().age
    )SRC").shouldVerified(true);

    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 0);
}

TEST_F(defFuncTest, defFuncDuplicateNegative) {
    make().negative().parse(R"SRC(
        a(n int) void
            ret
        a(n int) int
            ret n
        main() void
            ret
    )SRC").shouldVerified(false);
}

TEST_F(defFuncTest, defFuncDuplicate) {
    make().parse(R"SRC(
        a() void
            ret
        a(n int) int
            ret n
        main() void
            ret
    )SRC").shouldVerified(true);
}
