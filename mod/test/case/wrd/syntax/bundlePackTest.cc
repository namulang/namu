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

TEST_F(bundlePackTest, defaultDef3) {
    make().parse(R"SRC(
        main() void
            sys.con.print("please enter your name: ")
            name := sys.con.input()
            sys.con.print("hello, " + name + "!\n")
    )SRC").shouldVerified(true);
    run();
}
