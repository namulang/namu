#include "../TestManager.hpp"

WRD_TEST_START(ChunksTest)
	Chunks chks1;
	T(chks1.getBlkSize() == 0)
	T(chks1.getLen() == 0)
	T(chks1.getSize() == 0)
	T(chks1.get(0).isNull())
	T(chks1[-1].isNull())
	
	class Heap {
	public:
		void new1(Chunks& chk, wcnt cnt) {
			for(int n=0; n < cnt ; n++)
				ptrs.push_back(chk.new1());
		}
		void release(Chunks& chk) {
		    chk.release();
		    ptrs.clear();
		}
		std::vector<void*> ptrs;
	} heap;
	Chunks chks2(4);
	heap.new1(chks2, 1);
	T(chks2.getLen() == 1)
	T(chks2.getSize() == 1)
	T(heap.ptrs[0])
	
	heap.new1(chks2, 4);
	T(chks2.getLen() == 1)
	T(chks2.getSize() == 1)
	
	heap.release(chks2);
	T(chks2.getLen() == 0)
	T(chks2.getSize() == 0)
	T(chks2[0].isNull())
	T(chks2[-1].isNull())
	
	T( ! chks2.resize(3))
	T(chks2.getLen() == 3)
	T(chks2.getSize() == 3)
	T(chks2[0].isExist())
	T( ! chks2.release())
	
	heap.new1(chks2, 10);
	heap.release(chks2);
	T(chks2.getLen() == 0)
	T(chks2.getSize() == 0)
	
	heap.new1(chks2, 100);
	heap.release(chks2);
	T(chks2.getLen() == 0)
	T(chks2.getSize() == 0)
	
	heap.new1(chks2, 1000);
	heap.release(chks2);
	T(chks2.getLen() == 0)
	T(chks2.getSize() == 0)
	
	heap.new1(chks2, 10000);
	heap.release(chks2);
	T(chks2.getLen() == 0)
	T(chks2.getSize() == 0)
	
	heap.new1(chks2, 100000);
	heap.release(chks2);
	T(chks2.getLen() == 0)
	T(chks2.getSize() == 0)
	return "";
WRD_TEST_END(ChunksTest)
