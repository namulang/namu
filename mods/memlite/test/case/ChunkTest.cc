#include "../common/dep.hpp"

namespace wrd { namespace memlite {

    TEST(ChunkTest, MemoryHaverTest) {
        Chunk chk(4, false);

        ASSERT_EQ(chk.getLen(), 0);
        ASSERT_EQ(chk.getSize(), 0);
        ASSERT_EQ(chk[0], chk.get(0));
        ASSERT_FALSE(chk[1]);
        ASSERT_FALSE(chk[-1]);
        ASSERT_TRUE(chk.isFull());
        ASSERT_FALSE(chk.isCapable());
        ASSERT_FALSE(chk.has(nulr<Instance>()));
    }

    TEST(ChunkTest, AllocatorTest) {
        Chunk chk(4, false);

        ASSERT_EQ(chk.getBlkSize(), 4);
        ASSERT_TRUE(chk.rel());
        ASSERT_EQ(chk.getLen(), 0);
        ASSERT_EQ(chk.getSize(), 0);
        ASSERT_FALSE(chk.getEOB());
        ASSERT_FALSE(chk.getHeap());
    }

}}
