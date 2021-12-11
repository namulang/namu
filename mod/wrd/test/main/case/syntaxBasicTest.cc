#include "../common/dep.hpp"

using namespace wrd;
using namespace std;

namespace {
    struct syntaxBasicTest : public ::testing::Test {
        void SetUp() {}
        void TearDown() {}

        str parse(const wchar* src) {
            parser p;
            str ret = p.parse(src);
            EXPECT_TRUE(ret.isBind());
            return ret;
        }

        wbool assertSame(str unit, const wchar* expect) {
            // TODO: run unit and gather output and compare it to expect
            return true;
        }

    };
}

TEST_F(syntaxBasicTest, testHelloWorld) {
    parse(R"SRC(
        import cons

        main() void
            cons.out('hello world!')
    )SRC");

    //TODO: const char* expectOut = "hello world!";
}
