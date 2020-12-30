#include "../common/dep.hpp"

namespace wrd { namespace memlite {

	class Heap {
	public:
		void new1(Chunks& chk, wcnt cnt) {
			for(int n=0; n < cnt ; n++)
				ptrs.push_back(chk.new1());
		}
		void rel(Chunks& chk) {
		    chk.rel();
		    ptrs.clear();
		}
		std::vector<void*> ptrs;
	};

    TEST(ChunksTest, initialStateTest) {
        Chunks chks1;

        ASSERT_EQ(chks1.getBlkSize(), 0);
        ASSERT_EQ(chks1.getLen(), 0);
        ASSERT_EQ(chks1.getSize(), 0);
        ASSERT_TRUE(nul(chks1.get(0)));
        ASSERT_TRUE(nul(chks1[-1]));
    }

    TEST(ChunksTest, resizeFewTimesTest) {
        Heap heap;
        Chunks chks2(4);

        heap.new1(chks2, 1);
        ASSERT_EQ(chks2.getLen(), 1);
        ASSERT_EQ(chks2.getSize(), 1);
        ASSERT_TRUE(heap.ptrs[0]);

        heap.new1(chks2, 4);
        ASSERT_EQ(chks2.getLen(), 1);
        ASSERT_EQ(chks2.getSize(), 1);

        heap.rel(chks2);
        ASSERT_EQ(chks2.getLen(), 0);
        ASSERT_EQ(chks2.getSize(), 0);
        ASSERT_TRUE(nul(chks2[0]));
        ASSERT_TRUE(nul(chks2[-1]));

        ASSERT_TRUE(chks2.resize(3));
        ASSERT_EQ(chks2.getLen(), 3);
        ASSERT_EQ(chks2.getSize(), 3);
        ASSERT_FALSE(nul(chks2[0]));
        ASSERT_TRUE(chks2.rel());
    }

    TEST(ChunksTest, resizeLotsOfTimesTest) {
        Heap heap;
        Chunks chks2(4);

        heap.new1(chks2, 10);
        heap.rel(chks2);
        ASSERT_EQ(chks2.getLen(), 0);
        ASSERT_EQ(chks2.getSize(), 0);

        heap.new1(chks2, 100);
        heap.rel(chks2);
        ASSERT_EQ(chks2.getLen(), 0);
        ASSERT_EQ(chks2.getSize(), 0);

        heap.new1(chks2, 1000);
        heap.rel(chks2);
        ASSERT_EQ(chks2.getLen(), 0);
        ASSERT_EQ(chks2.getSize(), 0);

        heap.new1(chks2, 10000);
        heap.rel(chks2);
        ASSERT_EQ(chks2.getLen(), 0);
        ASSERT_EQ(chks2.getSize(), 0);

        heap.new1(chks2, 100000);
        heap.rel(chks2);
        ASSERT_EQ(chks2.getLen(), 0);
        ASSERT_EQ(chks2.getSize(), 0);
    }
}}
