#pragma once

#include "memlite/pool/chunk.hpp"
#include "memlite/watcher/watchCell.hpp"

namespace nm {

    class _nout watcher: public chunk {
        NM_ME(watcher, chunk)
        NM_INIT_META(me)
        friend class instancer;
        friend class bindTag;

    public:
        //  watcher:
        watcher();

    public:
        watchCell* get(nidx n);
        watchCell* get(id newId);
        const watchCell* get(nidx n) const NM_CONST_FUNC(get(n))
        const watchCell* get(id newId) const NM_CONST_FUNC(get(newId))
        //  Allocator:
        void* new1() override;

        nbool del(void* used, ncnt sz) override;

    protected:
        //  watcher:
        id _genId(void* pt) const;
        nidx _getIdx(void* it) const;
    };
} // namespace nm
