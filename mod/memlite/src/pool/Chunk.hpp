#pragma once

#include "Allocator.hpp"

namespace wrd {

    class Chunk : public Allocator {
        WRD_DECL_THIS(Chunk, Allocator)
        WRD_INIT_META(This)
        friend class Watcher;

    public:
        //  Chunk:
        static constexpr wcnt INIT_SZ = 20;

        Chunk(wcnt blksize = 1, wbool is_fixed = true);
        virtual ~Chunk();

        void* operator[](widx n) { return get(n); }

        void* get(widx n) { return _get(n); }
        wbool isFixed();
        //  Allocator:
        void* new1() override;
        wbool del(void* used, wcnt) override;
        /// @remark @ref Chunk can resize its data. but can't persist whole memory allocated before,
        ///         it's a kind of memory flashing and can't give a way for accessing it.
        ///         at outside, ptr for them should be daggled.
        wbool resize(wcnt new_sz) override;
        //  MemoryHaver:
        wcnt getLen() override;
        wcnt getSize() override;
        wbool rel() override;
        wbool has(Instance& it) override;

    protected:
        //  MemoryHaver:
        /// @return returns regarding current size, not length.
        ///         can return garbage if size is bigger than n.
        void* _onGet(widx n) override;

    private:
        //  Chunk:
        wuchar* _getEOB();
        wuchar* _getHeap();
        wbool _index(widx start);
        wcnt _getRealBlkSize();
        void* _allocHeap(wcnt new_sz);
        wbool _freeHeap(wuchar** heap);

        widx _head;
        wcnt _len, _sz;
        wuchar* _heap;
        wbool _isFixed;
    };
}
