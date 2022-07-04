#include "../../../wrdSyntaxTest.hpp"

using namespace wrd;
using namespace std;

namespace {
    struct bundlePackTest : public wrdSyntaxTest {};
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
