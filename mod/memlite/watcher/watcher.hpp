#pragma once

#include "../pool/chunk.hpp"
#include "watchCell.hpp"

namespace namu {

    class _wout watcher : public chunk {
        WRD_DECL_ME(watcher, chunk)
        WRD_INIT_META(me)
        friend class instancer;
        friend class bindTag;

    public:
        //  watcher:
        watcher();

        watchCell& operator[](widx n);
        watchCell& operator[](id newId);
        const watchCell& operator[](widx n) const WRD_UNCONST_FUNC(operator[](n))
        const watchCell& operator[](id newId) const WRD_UNCONST_FUNC(operator[](newId))

        watchCell& get(widx n);
        watchCell& get(id newId);
        const watchCell& get(widx n) const WRD_UNCONST_FUNC(get(n));
        const watchCell& get(id newId) const WRD_UNCONST_FUNC(get(newId));
        //  Allocator:
        void* new1() override;

        wbool del(void* used, wcnt sz) override;

    protected:
        //  watcher:
        id _genId(void* pt) const;
        widx _getIdx(void* it) const;
    };
}
