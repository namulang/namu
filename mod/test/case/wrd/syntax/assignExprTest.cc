#include "../../../wrdSyntaxTest.hpp"

using namespace wrd;
using namespace std;

namespace {
    struct assignExprTest : public wrdSyntaxTest {};
}

/*TEST_F(assignExprTest, distinguishDefineFuncOrCall) {
    if(make().parse(R"SRC(
        age int
        main() void
            age = 5
    )SRC").shouldParsed(true)) {
        node& res = getSubPack();
        ASSERT_FALSE(nul(res));

        const wInt& o = res.sub<wInt>("age");
        ASSERT_FALSE(nul(o));
        ASSERT_EQ(o.cast<wint>(), 5);
    }
}*/
