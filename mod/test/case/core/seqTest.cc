#include "../../namuTest.hpp"
#include <chrono>

using namespace namu;
using namespace std;

struct seqTest : public namuTest {};

TEST_F(seqTest, basicBehaviour) {
    nseq s(1, 10);
    ASSERT_EQ(s[0], 1);
    ASSERT_EQ(s[9], 9);

    ASSERT_EQ(s.len(), 9);

    ASSERT_EQ(s[10], s[9]);
    ASSERT_EQ(s[-1], s[0]);
}

TEST_F(seqTest, basicBehaviorOfSeq) {
    seq s(1, 10);
    ASSERT_EQ(s[0], 1);
    ASSERT_EQ(s[9], 9);

    ASSERT_EQ(s.len(), 9);

    ASSERT_EQ(s[10], s[9]);
    ASSERT_EQ(s[-1], s[0]);
}

TEST_F(seqTest, basicManagedBehaviorOfSeq) {
    seq s(1, 10);
    str ret = s.run("len");
    ASSERT_TRUE(ret);
    ASSERT_EQ(ret->cast<nint>(), s.len());

    ret = s.run("get", args{narr{*new nInt(0)}});
    ASSERT_TRUE(ret);
    ASSERT_EQ(ret->cast<nint>(), s[0]);

    ret = s.run("get", args{narr{*new nInt(-1)}});
    ASSERT_TRUE(ret);
    ASSERT_EQ(ret->cast<nint>(), s[-1]);

    ret = s.run("get", args{narr{*new nInt(9)}});
    ASSERT_TRUE(ret);
    ASSERT_EQ(ret->cast<nint>(), s[9]);

    ret = s.run("get", args{narr{*new nInt(10)}});
    ASSERT_TRUE(ret);
    ASSERT_EQ(ret->cast<nint>(), s[10]);
}

TEST_F(seqTest, eachReturnedValueShouldBeDifferent) {
    seq s(1, 10); // [1, 10)

    str ret = s.run("get", args{narr{*new nInt(0)}});
    ASSERT_TRUE(ret);
    ASSERT_EQ(ret->cast<nint>(), s[0]);
    str ret2 = s.run("get", args{narr{*new nInt(1)}});
    ASSERT_TRUE(ret2);
    ASSERT_EQ(ret2->cast<nint>(), s[1]);

    ASSERT_EQ(ret->cast<nint>(), s[0]);
}
