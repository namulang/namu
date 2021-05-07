#include "../common/dep.hpp"

using namespace wrd;
using namespace std;

namespace {
}

TEST(primitiveObjTest, testCreateWIntInMgd) {
    wInt origin(1);

    tstr<wInt> inst(origin.run(narr({&origin})));
    ASSERT_TRUE(inst);
    ASSERT_EQ(origin.get(), inst->get());
    ASSERT_NE(&origin, &(*inst));
}

TEST(primitiveObjTest, testCloneWIntInMgd) {
    wInt origin(1);

    tstr<wInt> inst(origin.clone());
    ASSERT_TRUE(inst);
    ASSERT_EQ(origin.get(), inst->get());
    ASSERT_NE(&origin, &(*inst));
}

TEST(primitiveObjTest, testDefaultCtor) {
    wInt origin(1);

    tstr<wInt> inst(origin.run(narr()));
    ASSERT_TRUE(inst);
    ASSERT_EQ(inst->get(), 0);
}
