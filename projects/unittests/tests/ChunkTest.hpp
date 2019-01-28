#pragma once

#include "../TestCase.hpp"

WRD_TESTCASE(ChunkTest, (
	//	Basic test:
	Chunk chk(4, true);
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
		void new1(Chunk& chk, wcnt cnt) {
			for(int n=0; n < cnt ; n++)
				ptrs.push_back(chk.new1());
		}
		void del(Chunk& chk) {
			for(void* e : ptrs)
				chk.del(e, chk.getBlkSize());
			ptrs.clear();
		}
		std::vector<void*> ptrs;
	};
	Heap heap;
	T(chk.isFixed())
	heap.new1(chk, 1);
	T(chk.getLen() == 1)
	T(chk.getSize() >= 1)
	T(chk[0])
	T(chk[0] == heap.ptrs[0])
	T( ! chk[-1])
	T(chk.getEOB())
	T(chk.getHeap())

	heap.new1(chk, 1);
	T(chk.getLen() == 2)
	T(chk.getSize() >= chk.getLen())
	T(chk[1])
	T(chk.has(*(Instance*)chk[1]))
	T( chk.getBlkSize() == 4)

	heap.del(chk);
	T(chk.getLen() == 0)
	T(chk.getSize() >= 2)
	T( ! chk[0])
	T(chk.getHeap())
	T(  chk.getBlkSize() == 4)

	T(chk.release())
	T(chk.getSize() == 0)
	T( ! chk.getHeap())
	T(   chk.getBlkSize() == 4)
	T(chk.isFixed())

	T( ! chk.resize(5))
	T(chk.getSize() == 5)
	T(chk.getLen() == 0)
	T(chk[4] == chk[0])
	T(chk[0] == chk[-1])
	T(chk[-1] == NULL)
	T(chk.getHeap())
	T(chk.getEOB())
	T( ! chk.isFull())
	T(chk.isCapable())

	heap.new1(chk, 10);
	heap.del(chk);
	T( ! chk.getLen())

	heap.new1(chk, 100);
	heap.del(chk);
	T( ! chk.getLen())

	heap.new1(chk, 1000);
	heap.del(chk);
	T( ! chk.getLen())

	heap.new1(chk, 10000);
	heap.del(chk);
	T( ! chk.getLen())

	heap.new1(chk, 100000);
	heap.del(chk);
	T( ! chk.getLen())

	//	fixed chunk:
	Chunk fixed(100);
	T(fixed.getLen() == 0)
	T(fixed.getSize() == 1)
	T(fixed[0] == fixed.get(0))
	T( ! fixed[1])
	T( ! fixed[-1])
	T( ! fixed.isFull())
	T(fixed.isCapable())
	T( ! fixed.has(*(Instance*) NULL))
	//		Allocator:
	T(fixed.getBlkSize() == 4)
	T( ! fixed.release())
	T(fixed.getLen() == 0)
	T(fixed.getSize() == 1)
	T( ! fixed.getEOB())
	T( ! fixed.getHeap())

	T(fixed.isFixed())
	heap.new1(fixed, 1);
	T(fixed.getLen() == 1)
	T(fixed.getSize() >= 1)
	T(fixed[0])
	T(fixed[0] == heap.ptrs[0])
	T( ! fixed[-1])
	T(fixed.getEOB())
	T(fixed.getHeap())

	heap.new1(fixed, 1);
	T(fixed.getLen() == 2)
	T(fixed.getSize() >= fixed.getLen())
	T(fixed[1])
	T(fixed.has(*(Instance*)fixed[1]))
	T(fixed.getBlkSize() == 4)

	heap.del(fixed);
	T(fixed.getLen() == 0)
	T(fixed.getSize() >= 2)
	T( ! fixed[0])
	T(fixed.getHeap())
	T(fixed.getBlkSize() == 4)

	T(fixed.release())
	T(fixed.getSize() == 0)
	T( ! fixed.getHeap())
	T(fixed.getBlkSize() == 4)
	T(fixed.isFixed())

	heap.new1(fixed, 10);
	heap.del(fixed);
	T( ! fixed.getLen())

	heap.new1(fixed, 100);
	heap.del(fixed);
	T( ! fixed.getLen())

	heap.new1(fixed, 1000);
	heap.del(fixed);
	T( ! fixed.getLen())

	heap.new1(fixed, 10000);
	heap.del(fixed);
	T( ! fixed.getLen())

	heap.new1(fixed, 100000);
	heap.del(fixed);
	T( ! fixed.getLen())
	return "";
))
