#include "../../../wrdSyntaxTest.hpp"

using namespace wrd;
using namespace std;

namespace {
    struct bundlePackTest : public wrdSyntaxTest {};
}

TEST_F(bundlePackTest, defaultDef) {
    make().parse(R"SRC(
        main() void
            samplePack.helloWorld.print("hello world!\n")
    )SRC").shouldVerified(true);
}
