#include "../common/dep.hpp"

using namespace wrd;
using namespace std;

namespace {
    struct syntaxExprTest : public ::testing::Test {
        void SetUp() {}
        void TearDown() {}

        str parse(const wchar* src) {
            parser p;
            str ret = p.parse(src);
            EXPECT_TRUE(ret.isBind()) << "test code: " << src << "\n";
            return ret;
        }

        void parseFail(const wchar* src) {
            parser p;
            str ret = p.parse(src);
            EXPECT_FALSE(ret.isBind()) << "test code: " << src << "\n";
        }

        wbool assertSame(str unit, const wchar* expect) {
            // TODO: run unit and gather output and compare it to expect
            return true;
        }

    };
}

TEST_F(syntaxExprTest, exprTest) {
    parse(R"SRC(
if
            22
            if
                    33)SRC");
}

TEST_F(syntaxExprTest, test2) {
    parse(R"SRC(
if
            'hell   "   o'
            if
                    "hel'lo")SRC");
}

TEST_F(syntaxExprTest, stringLiteralShouldFail) {
    parseFail(R"SRC(
if
            'he
            ll'
            if
                    "hel'lo")SRC");
}

TEST_F(syntaxExprTest, exprTest3) {
    parse(R"SRC(
   if
    2 + 3*27 + 44 - 27/34*43 - 1
    )SRC");
}

/*TEST_F(syntaxExprTest, testParseHelloWorld) {
    parse(R"SRC(
        main() void
            out('hello world!')
    )SRC"); // this code can't be run, but can be parsed.
}

TEST_F(syntaxExprTest, testHelloWorld) {
    auto unit = parse(R"SRC(
    parse(R"SRC(
        import cons

        main() void
            cons.out('hello world!')
    )SRC");
    ASSERT_FALSE(nul(unit));
    //TODO: const char* expectOut = "hello world!";
}*/
