#pragma once

#include "../pool/chunk.hpp"
#include "watchCell.hpp"

namespace namu {

    class _nout watcher : public chunk {
        NAMU_DECL_ME(watcher, chunk)
        NAMU_INIT_META(me)
        friend class instancer;
        friend class bindTag;

    public:
        //  watcher:
        watcher();

        watchCell& operator[](nidx n);
        watchCell& operator[](id newId);
        const watchCell& operator[](nidx n) const NAMU_UNCONST_FUNC(operator[](n))
        const watchCell& operator[](id newId) const NAMU_UNCONST_FUNC(operator[](newId))

        watchCell& get(nidx n);
        watchCell& get(id newId);
        const watchCell& get(nidx n) const NAMU_UNCONST_FUNC(get(n));
        const watchCell& get(id newId) const NAMU_UNCONST_FUNC(get(newId));
        //  Allocator:
        void* new1() override;

        nbool del(void* used, ncnt sz) override;

    protected:
        //  watcher:
        id _genId(void* pt) const;
        nidx _getIdx(void* it) const;
    };
}
