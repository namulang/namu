#pragma once

#include "Allocator.hpp"

namespace wrd {

    class Chunk : public Allocator {
        WRD_DECL_THIS(Chunk, Allocator)
        WRD_INIT_META(This)
        friend class Watcher;

    public:
        //  Chunk:
        static constexpr wcnt MIN_SZ = 20;

        Chunk(wcnt blockSz=1, wcnt sz=MIN_SZ);
        ~Chunk();

        void* operator[](widx n) { return get(n); }

        void* get(widx n) { return _get(n); }

        //  Allocator:
        void* new1() override;
        wbool del(void* used, wcnt) override;
        //  MemoryHaver:
        wcnt getLen() const override;
        wcnt getSize() const override;
        wbool rel() override;
        wbool has(const Instance& it) const override;

    protected:
        //  MemoryHaver:
        /// @return returns regarding current size, not length.
        ///         can return garbage if size is bigger than n.
        void* _get(widx n) override;
        wuchar* _getHeap();
        const wuchar* _getHeap() const WRD_UNCONST_FUNC(_getHeap())
        wbool _resize(wcnt newSz);

    private:
        //  Chunk:
        const wuchar* _getEOB() const WRD_UNCONST_FUNC(_getEOB())
        wuchar* _getEOB();
        wbool _index(widx start);
        wcnt _getRealBlkSize();
        void* _allocHeap(wcnt new_sz);
        wbool _freeHeap(wuchar** heap);

        widx _head;
        wcnt _len, _sz;
        wuchar* _heap;
    };
}
