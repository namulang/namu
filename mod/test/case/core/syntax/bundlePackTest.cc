#include "../../../namuSyntaxTest.hpp"

using namespace namu;
using namespace std;

namespace {
    struct bundlePackTest : public namuSyntaxTest {};
}

TEST_F(bundlePackTest, defaultDef) {
    make().parse(R"SRC(
        main() void
            sys.con.print("hello \\tworld!\n")
    )SRC").shouldVerified(true);
    run();
}

TEST_F(bundlePackTest, defaultDef2) {
    make().parse(R"SRC(
        msg := "hello\t"
        main() void
            sys.con.print(msg + "world!\n")
    )SRC").shouldVerified(true);
    run();
}

TEST_F(bundlePackTest, withAsNegative) {
    make().parse(R"SRC(
        Helloworld(age int) int
            return age

        main() int
            a := Helloworld('g')
            sys.con.print(a as str)
            return 0
    )SRC").shouldParsed(true);
    shouldVerified(false);
}

TEST_F(bundlePackTest, withAs) {
    make().parse(R"SRC(
        Helloworld(age int) int
            return age

        main() int
            a := Helloworld('g' as int)
            sys.con.print(a as str)
            return 0
    )SRC").shouldVerified(true);
    run();
}

TEST_F(bundlePackTest, defaultDef3) {
    make().parse(R"SRC(
        age int
        ge int 

        main() int
            age = 48268
            ge = age + 3985
            sys.con.print(age as str + " \n")
            sys.con.print(ge as str)
            return ge
    )SRC").shouldVerified(true);
    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<int>(), 48268 + 3985);
}
