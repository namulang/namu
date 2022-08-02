#include "../../namuTest.hpp"

using namespace namu;
using namespace std;

struct primitiveObjTest : public namuTest {};

TEST_F(primitiveObjTest, testCloneWIntInMgd) {
    wInt origin(1);

    tstr<wInt> inst(origin.clone());
    ASSERT_TRUE(inst);
    ASSERT_EQ(origin.get(), inst->get());
    ASSERT_NE(&origin, &(*inst));
}

TEST_F(primitiveObjTest, subsIsDummy) {
    wInt val(2);
    int initial = val.subs().len();

    bicontainable& subs = val.subs();
    ASSERT_FALSE(nul(subs));
    subs.add("not work", new wInt(3));
    ASSERT_EQ(subs.len(), initial);
    ASSERT_FALSE(subs.has("not work"));
    ASSERT_FALSE(subs.begin().isEnd());
}
