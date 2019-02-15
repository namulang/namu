#include "../TestCase.hpp"

WRD_TEST_START(ChunkTest)
	//	Basic test:
	Chunk chk(4, false);
	//		MemoryHaver:
	T(chk.getLen() == 0)
	T(chk.getSize() == 0)
	T(chk[0] == chk.get(0))
	T( ! chk[1])
	T( ! chk[-1])
	T(chk.isFull())
	T( ! chk.isCapable())
	T( ! chk.has(*(Instance*) NULL))
	//		Allocator:
	T(chk.getBlkSize() == 4)
	T( ! chk.release())
	T(chk.getLen() == 0)
	T(chk.getSize() == 0)
	T( ! chk.getEOB())
	T( ! chk.getHeap())

	//		Chunk:
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
		wbool release(Chunk& chk) {
			if(chk.release()) return false;
			ptrs.clear();
			return true;
		}
		std::vector<void*> ptrs;
	};
	Heap heap;
	T( ! chk.isFixed())
	T(heap.new1(chk, 1))
	T(chk.getLen() == 1)
	T(chk.getSize() == Chunk::INIT_SZ)
	T(chk[0])
	T(chk[0] == heap.ptrs[0])
	T( ! chk[-1])
	T(chk.getEOB())
	T(chk.getHeap())

	T(heap.new1(chk, 1))
	T(chk.getLen() == 2)
	T(chk.getSize() >= chk.getLen())
	T(chk[1])
	T(chk.has(*(Instance*)chk[1]))
	T( chk.getBlkSize() == 4)

	T(heap.release(chk))
	T(chk.getLen() == 0)
	T(chk.getSize() == 0)
	T( ! chk[0])
	T( ! chk.getHeap())
	T(chk.getBlkSize() == 4)

	T( ! chk.release())
	T(chk.getSize() == 0)
	T( ! chk.getHeap())
	T(chk.getBlkSize() == 4)
	T( ! chk.isFixed())

	T( ! chk.resize(5))
	T(chk.getSize() == Chunk::INIT_SZ)
	T( ! chk.resize(Chunk::INIT_SZ+5))
	T(chk.getSize() == Chunk::INIT_SZ+5)
	T(chk.getLen() == 0)
	T(chk[4] == chk[0])
	T(chk[0] == chk[-1])
	T(chk[-1] == NULL)
	T(chk.getHeap())
	T(chk.getEOB())
	T( ! chk.isFull())
	T(chk.isCapable())

	T(heap.new1(chk, 10))
	T(heap.release(chk))
	T( ! chk.getLen())

	T(heap.new1(chk, 100))
	T( ! chk.resize(105))
	T(chk.getLen() == 100)
	T(chk.getSize() > 100)
	T(chk[0])
	T(chk[100] == NULL)
	T(heap.release(chk))
	T( ! chk.getLen())

	T(heap.new1(chk, 1000))
	T(heap.release(chk))
	T( ! chk.getLen())

	T(heap.new1(chk, 10000))
	T(heap.release(chk))
	T( ! chk.getLen())

	T(heap.new1(chk, 100000))
	T(heap.release(chk))
	T( ! chk.getLen())

	//	fixed chunk:
	Chunk fixed(100);
	T(fixed.getLen() == 0)
	T(fixed.getSize() == 0)
	T(fixed[0] == fixed.get(0))
	T( ! fixed[1])
	T( ! fixed[-1])
	T(fixed.isFull())
	T( ! fixed.isCapable())
	T( ! fixed.has(*(Instance*) NULL))
	//		Allocator:
	T(fixed.getBlkSize() == 100)
	T( ! fixed.release())
	T(fixed.getLen() == 0)
	T(fixed.getSize() == 0)
	T( ! fixed.getEOB())
	T( ! fixed.getHeap())

	T(fixed.isFixed())
	T(heap.new1(fixed, 1))
	T(fixed.getLen() == 1)
	T(fixed.getSize() >= 1)
	T(fixed[0])
	T(fixed[0] == heap.ptrs[0])
	T( ! fixed[-1])
	T(fixed.getEOB())
	T(fixed.getHeap())

	T(heap.new1(fixed, 1))
	T(fixed.getLen() == 2)
	T(fixed.getSize() >= fixed.getLen())
	T(fixed[1])
	T(fixed.has(*(Instance*)fixed[1]))
	T(fixed.getBlkSize() == 100)

	T(heap.release(fixed))
	T(fixed.getLen() == 0)
	T(fixed.getSize() == 0)
	T( ! fixed[0])
	T( ! fixed.getHeap())
	T(fixed.getBlkSize() == 100)

	T( ! fixed.release())
	T(fixed.getSize() == 0)
	T( ! fixed.getHeap())
	T(fixed.getBlkSize() == 100)
	T(fixed.isFixed())

	T(heap.new1(fixed, 10))
	T(fixed.getLen() == 10)
	T(heap.release(fixed))
	T(fixed.getLen() == 0)

	T( ! heap.new1(fixed, 100))
	T(fixed.getLen() == 20)
	T(heap.release(fixed))
	T(fixed.getLen() == 0)

	T( ! heap.new1(fixed, 1000))
	T(fixed.getLen() == 20)
	T(heap.release(fixed))
	T(fixed.getLen() == 0)

	T( ! heap.new1(fixed, 10000))
	T(fixed.getLen() == 20)
	T(heap.release(fixed))
	T(fixed.getLen() == 0)

	T( ! heap.new1(fixed, 100000))
	T(fixed.getLen() == 20)
	T(heap.release(fixed))
	T(fixed.getLen() == 0)

	return "";
WRD_TEST_END(ChunkTest)
