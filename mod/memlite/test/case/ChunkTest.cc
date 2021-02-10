#include "../common/dep.hpp"

using namespace wrd;

TEST(ChunkTest, MemoryHaverTest) {
    Chunk chk(4, false);

    ASSERT_EQ(chk.getLen(), 0);
    ASSERT_EQ(chk.getSize(), 0);
    ASSERT_EQ(chk[0], chk.get(0));
    ASSERT_FALSE(chk[1]);
    ASSERT_FALSE(chk[-1]);
    ASSERT_TRUE(chk.isFull());
    ASSERT_FALSE(chk.isCapable());
    ASSERT_FALSE(chk.has(nulOf<Instance>()));
}

TEST(ChunkTest, AllocatorTest) {
    Chunk chk(4, false);

    ASSERT_EQ(chk.getBlkSize(), 4);
    ASSERT_TRUE(chk.rel());
    ASSERT_EQ(chk.getLen(), 0);
    ASSERT_EQ(chk.getSize(), 0);
}

TEST(ChunkTest, ChunkListTest) {
    class Heap {
    public:
        wbool new1(Chunk& chk, wcnt cnt) {
            for(int n=0; n < cnt ; n++)
            {
                void* ptr = chk.new1();
                ptrs.push_back(ptr);
                if(!ptr)
                    return false;
            }
            return true;
        }
        wbool rel(Chunk& chk) {
            if(!chk.rel()) return false;
            ptrs.clear();
            return true;
        }
        std::vector<void*> ptrs;
    } heap;
    Chunk chk(4, false);

    ASSERT_FALSE(chk.isFixed());
    ASSERT_TRUE(heap.new1(chk, 1));
    ASSERT_EQ(chk.getLen(), 1);
    ASSERT_EQ(chk.getSize(), Chunk::INIT_SZ);
    ASSERT_TRUE(chk[0]);
    ASSERT_EQ(chk[0], heap.ptrs[0]);
    ASSERT_FALSE(chk[-1]);

    ASSERT_TRUE(heap.new1(chk, 1));
    ASSERT_EQ(chk.getLen(), 2);
    ASSERT_GE(chk.getSize(), chk.getLen());
    ASSERT_TRUE(chk[1]);
    ASSERT_TRUE(chk.has(*(Instance*)chk[1]));
    ASSERT_EQ(chk.getBlkSize(), 4);

    ASSERT_TRUE(heap.rel(chk));
    ASSERT_EQ(chk.getLen(), 0);
    ASSERT_EQ(chk.getSize(), 0);
    ASSERT_FALSE(chk[0]);
    ASSERT_EQ(chk.getBlkSize(), 4);

    ASSERT_TRUE(chk.rel());
    ASSERT_EQ(chk.getSize(), 0);
    ASSERT_EQ(chk.getBlkSize(), 4);
    ASSERT_FALSE(chk.isFixed());

    ASSERT_TRUE(chk.resize(5));
    ASSERT_EQ(chk.getSize(), Chunk::INIT_SZ);
    ASSERT_TRUE(chk.resize(Chunk::INIT_SZ + 5));
    ASSERT_EQ(chk.getSize(), Chunk::INIT_SZ + 5);
    ASSERT_EQ(chk.getLen(), 0);
    ASSERT_EQ(chk[4], chk[0]);
    ASSERT_EQ(chk[0], chk[-1]);
    ASSERT_TRUE(chk[-1] == WRD_NULL);
    ASSERT_FALSE(chk.isFull());
    ASSERT_TRUE(chk.isCapable());

    ASSERT_TRUE(heap.new1(chk, 10));
    ASSERT_TRUE(heap.rel(chk));
    ASSERT_FALSE(chk.getLen());

    ASSERT_TRUE(heap.new1(chk, 100));
    ASSERT_TRUE(chk.resize(105));
    ASSERT_EQ(chk.getLen(), 100);
    ASSERT_GT(chk.getSize(), 100);
    ASSERT_TRUE(chk[0]);
    ASSERT_TRUE(chk[100] == WRD_NULL);
    ASSERT_TRUE(heap.rel(chk));
    ASSERT_FALSE(chk.getLen());

    ASSERT_TRUE(heap.new1(chk, 1000));
    ASSERT_TRUE(heap.rel(chk));
    ASSERT_FALSE(chk.getLen());

    ASSERT_TRUE(heap.new1(chk, 10000));
    ASSERT_TRUE(heap.rel(chk));
    ASSERT_FALSE(chk.getLen());

    ASSERT_TRUE(heap.new1(chk, 100000));
    ASSERT_TRUE(heap.rel(chk));
    ASSERT_FALSE(chk.getLen());
}
