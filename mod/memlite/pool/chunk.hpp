#pragma once

#include "allocator.hpp"

namespace namu {

    class _wout chunk : public allocator {
        WRD_DECL_ME(chunk, allocator)
        WRD_INIT_META(me)
        friend class watcher;

    public:
        //  chunk:
        static constexpr wcnt MIN_SZ = 20;

        explicit chunk(wcnt blockSz=1, wcnt sz=MIN_SZ);
        ~chunk();

        void* operator[](widx n) { return get(n); }

        void* get(widx n) { return _get(n); }

        //  allocator:
        void* new1() override;
        wbool del(void* used, wcnt) override;
        //  MemoryHaver:
        wcnt len() const override;
        wcnt size() const override;
        wbool rel() override;
        wbool has(const instance& it) const override;

    protected:
        //  MemoryHaver:
        /// @return returns regarding current size, not length.
        ///         can return garbage if size is bigger than n.
        void* _get(widx n) override;
        wuchar* _getHeap();
        const wuchar* _getHeap() const WRD_UNCONST_FUNC(_getHeap())
        wbool _resize(wcnt newSz);

    private:
        //  chunk:
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
