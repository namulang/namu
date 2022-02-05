#include "../../syntaxTest.hpp"

using namespace wrd;
using namespace std;

namespace {
    struct syntaxPackTest : public syntaxTest {};
}

TEST_F(syntaxPackTest, parsePackTest) {
    make(manifest("demo")).parse(R"SRC(
pack demo
    )SRC").expect(true);
    ASSERT_FALSE(nul(getPack().subs()));
    ASSERT_EQ(getPack().subs().len(), 0);
    ASSERT_EQ(getPack().getName(), "demo");
}
