#include "../../../syntaxTest.hpp"

using namespace wrd;
using namespace std;

namespace {
    struct packTest : public syntaxTest {};
}

TEST_F(packTest, parsePackTest) {
    make(manifest("demo")).parse(R"SRC(
pack demo
    )SRC").expect(true);
    ASSERT_FALSE(nul(getSubPack()));
    ASSERT_FALSE(nul(getPack().subs()));
    ASSERT_EQ(getPack().subs().len(), 0);
    ASSERT_EQ(getPack().getName(), "demo");
}
