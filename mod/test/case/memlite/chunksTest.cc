#include "../../common/dep.hpp"

using namespace wrd;

class heap {
public:
    void new1(chunks& chk, wcnt cnt) {
        for(int n=0; n < cnt ; n++)
            ptrs.push_back(chk.new1());
    }
    void rel(chunks& chk) {
        chk.rel();
        ptrs.clear();
    }
    std::vector<void*> ptrs;
};

struct chunksTest : public ::testing::Test {
    void tearDown() {
        instance::_vault.getVaults().clear();
    }

    int getVaultsSize() {
        return instance::_vault.getVaults().size();
    }
};

TEST_F(chunksTest, initialStateTest) {
    chunks chks1;

    ASSERT_EQ(chks1.getBlkSize(), 0);
    ASSERT_EQ(chks1.len(), 0);
    ASSERT_EQ(chks1.size(), 0);
    ASSERT_TRUE(nul(chks1.get(0)));
    ASSERT_TRUE(nul(chks1[-1]));
}

TEST_F(chunksTest, resizeFewTimesTest) {
    heap heap;
    chunks chks2(4);

    heap.new1(chks2, 1);
    ASSERT_EQ(chks2.len(), 1);
    ASSERT_EQ(chks2.size(), 1);
    ASSERT_TRUE(heap.ptrs[0]);

    heap.new1(chks2, 4);
    ASSERT_EQ(chks2.len(), 1);
    ASSERT_EQ(chks2.size(), 1);

    heap.rel(chks2);
    ASSERT_EQ(chks2.len(), 0);
    ASSERT_EQ(chks2.size(), 0);
    ASSERT_TRUE(nul(chks2[0]));
    ASSERT_TRUE(nul(chks2[-1]));

    ASSERT_TRUE(chks2.resize(3));
    ASSERT_EQ(chks2.len(), 3);
    ASSERT_EQ(chks2.size(), 3);
    ASSERT_FALSE(nul(chks2[0]));
    ASSERT_TRUE(chks2.rel());
}

TEST_F(chunksTest, resizeLotsOfTimesTest) {
    heap heap;
    chunks chks2(4);

    heap.new1(chks2, 10);
    heap.rel(chks2);
    ASSERT_EQ(chks2.len(), 0);
    ASSERT_EQ(chks2.size(), 0);
    tearDown();
    ASSERT_EQ(getVaultsSize(), 0);

    heap.new1(chks2, 100);
    heap.rel(chks2);
    ASSERT_EQ(chks2.len(), 0);
    ASSERT_EQ(chks2.size(), 0);
    tearDown();
    ASSERT_EQ(getVaultsSize(), 0);

    heap.new1(chks2, 1000);
    heap.rel(chks2);
    ASSERT_EQ(chks2.len(), 0);
    ASSERT_EQ(chks2.size(), 0);
    tearDown();
    ASSERT_EQ(getVaultsSize(), 0);

    heap.new1(chks2, 10000);
    heap.rel(chks2);
    ASSERT_EQ(chks2.len(), 0);
    ASSERT_EQ(chks2.size(), 0);
    tearDown();
    ASSERT_EQ(getVaultsSize(), 0);

    heap.new1(chks2, 100000);
    heap.rel(chks2);
    ASSERT_EQ(chks2.len(), 0);
    ASSERT_EQ(chks2.size(), 0);
}
