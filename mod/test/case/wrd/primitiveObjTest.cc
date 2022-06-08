#include "../../wrdTest.hpp"

using namespace wrd;
using namespace std;

struct primitiveObjTest : public wrdTest {};

TEST_F(primitiveObjTest, testCreateWIntInMgd) {
    wInt origin(1);

    tstr<wInt> inst = origin.run(obj::CTOR_NAME, narr(origin));
    ASSERT_TRUE(inst);
    ASSERT_EQ(origin.get(), inst->get());
    ASSERT_NE(&origin, &(*inst));
}

TEST_F(primitiveObjTest, testCloneWIntInMgd) {
    wInt origin(1);

    tstr<wInt> inst(origin.clone());
    ASSERT_TRUE(inst);
    ASSERT_EQ(origin.get(), inst->get());
    ASSERT_NE(&origin, &(*inst));
}

TEST_F(primitiveObjTest, testDefaultCtor) {
    wInt origin(1);

    tstr<wInt> inst = origin.run(obj::CTOR_NAME, narr());
    ASSERT_TRUE(inst);
    ASSERT_EQ(inst->get(), 0);
}

TEST_F(primitiveObjTest, subsIsNotDummy) {
    wInt val(2);
    int initial = val.subs().len();

    bicontainable& subs = val.subs();
    ASSERT_FALSE(nul(subs));
    subs.add("not work", new wInt(3));
    ASSERT_EQ(subs.len(), initial+1);
    ASSERT_TRUE(subs.has("not work"));
    ASSERT_FALSE(subs.begin().isEnd());
}
