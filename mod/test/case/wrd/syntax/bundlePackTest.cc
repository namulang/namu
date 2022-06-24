#include "../../../wrdSyntaxTest.hpp"

using namespace wrd;
using namespace std;

namespace {
    struct bundlePackTest : public wrdSyntaxTest {};
}

TEST_F(bundlePackTest, defaultDef) {
    make().parse(R"SRC(
        main() void
            samplePack.helloWorld.print("hello \\tworld!\n")
    )SRC").shouldVerified(true);
    run();
}

/*TEST_F(bundlePackTest, defaultDef2) {
    make().parse(R"SRC(
        msg := "hello "
        main() void
            samplePack.helloWorld.print(msg + "world!\n")
    )SRC").shouldVerified(true);
    run();
}*/
