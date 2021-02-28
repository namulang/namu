#include "../common/dep.hpp"
#include <vector>

using namespace wrd;
using namespace std;

TEST(ChunkTest, MemoryHaverTest) {
    Chunk chk(4);

    EXPECT_EQ(chk.getLen(), 0);
    EXPECT_EQ(chk.getSize(), Chunk::MIN_SZ);
    EXPECT_EQ(chk[0], chk.get(0));
    EXPECT_TRUE(chk[1]);
    EXPECT_FALSE(chk[-1]);
    EXPECT_FALSE(chk.isFull());
    EXPECT_TRUE(chk.isCapable());
    EXPECT_FALSE(chk.has(nulOf<Instance>()));
}

TEST(ChunkTest, AllocatorTest) {
    Chunk chk(4);

    EXPECT_EQ(chk.getBlkSize(), 4);
    EXPECT_TRUE(chk.rel());
    EXPECT_EQ(chk.getLen(), 0);
    EXPECT_EQ(chk.getSize(), 0);
}

TEST(ChunkTest, ChunkListTest) {
    class Heap {
    public:
        wbool new1(Chunk& chk, wcnt cnt) {
            for(int n=0; n < cnt ; n++)
            {
                void* ptr = chk.new1();
                if(!ptr)
                    return false;
            }
            return true;
        }
    } heap;

    Chunk chk(4, 1112);

    EXPECT_TRUE(heap.new1(chk, 1));
    EXPECT_EQ(chk.getLen(), 1);
    EXPECT_EQ(chk.getSize(), 1112);
    EXPECT_TRUE(chk[0]);
    EXPECT_FALSE(chk[-1]);

    EXPECT_TRUE(heap.new1(chk, 1));
    EXPECT_EQ(chk.getLen(), 2);
    EXPECT_GE(chk.getSize(), chk.getLen());
    EXPECT_TRUE(chk[1]);
    EXPECT_TRUE(chk.has(*(Instance*)chk[1]));
    EXPECT_EQ(chk.getBlkSize(), 4);

    EXPECT_EQ(chk.getLen(), 2);
    EXPECT_EQ(chk.getSize(), 1112);
    EXPECT_TRUE(chk[0]);
    EXPECT_EQ(chk.getBlkSize(), 4);

    EXPECT_TRUE(heap.new1(chk, 10));
    EXPECT_EQ(chk.getLen(), 12);

    EXPECT_TRUE(heap.new1(chk, 100));
    EXPECT_EQ(chk.getLen(), 112);
    EXPECT_EQ(chk.getSize(), 1112);
    EXPECT_TRUE(chk[0]);
    EXPECT_TRUE(chk[100]);

    EXPECT_TRUE(heap.new1(chk, 1000));
    EXPECT_EQ(chk.getLen(), 1112);

    EXPECT_FALSE(heap.new1(chk, 1));
    EXPECT_NE(chk.getLen(), 1113);

    EXPECT_TRUE(chk.rel());
    EXPECT_EQ(chk.getSize(), 0);
    EXPECT_EQ(chk.getBlkSize(), 4);

    EXPECT_EQ(chk.getLen(), 0);
    EXPECT_FALSE(chk[4]);
    EXPECT_FALSE(chk[0]);
    EXPECT_TRUE(chk.isFull());
    EXPECT_FALSE(chk.isCapable());

}

void addIntegrityTest(Chunk& chk, int cnt) {
    for(int n=0; n < cnt ; n++) {
        int* val = (int*) chk.new1();
        *val = n;
    }

    for(int n=0; n < cnt ;n++) {
        int* actual = (int*) chk[n];
        EXPECT_EQ(*actual, n);
    }
}

TEST(ChunkTest, addIntegrityTest100) {
    Chunk chk(4, 100);
    addIntegrityTest(chk, 100);
}
TEST(ChunkTest, addIntegrityTest10000) {
    Chunk chk(4, 10000);
    addIntegrityTest(chk, 10000);
}
