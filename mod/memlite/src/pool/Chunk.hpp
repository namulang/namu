#pragma once

#include "Allocator.hpp"

namespace wrd {

    class Chunk : public Allocator {
        WRD_DECL_THIS(Chunk, Allocator)
        WRD_INIT_META(This)

    public:
        //  Chunk:
        static constexpr wcnt INIT_SZ = 20;

        Chunk(wcnt blksize = 1, wbool is_fixed = true);
        virtual ~Chunk();

        const wuchar* getEOB() const;
        const wuchar* getHeap() const;
        wbool isFixed() const;
        //  Allocator:
        void* new1();
        wbool del(void* used, wcnt);
        /// @remark @ref Chunk can resize its data. but can't persist whole memory allocated before,
        ///         it's a kind of memory flashing and can't give a way for accessing it.
        ///         at outside, ptr for them should be daggled.
        wbool resize(wcnt new_sz);
        //  MemoryHaver:
        wcnt getLen() const;
        wcnt getSize() const;
        wbool rel();
        wbool has(const Instance& it) const;

    protected:
        //  MemoryHaver:
        /// @return returns regarding current size, not length.
        ///         can return garbage if size is bigger than n.
        void* _get(widx n);

    private:
        //  Chunk:
        wuchar* _getEOB();
        wbool _index(widx start);
        wcnt _getRealBlkSize() const;
        void* _allocHeap(wcnt new_sz);
        wbool _freeHeap(wuchar** heap);

        widx _head;
        wcnt _len, _sz;
        wuchar* _heap;
        wbool _isFixed;
    };
}
