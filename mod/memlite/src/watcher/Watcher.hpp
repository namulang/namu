#pragma once

#include "../pool/Chunk.hpp"
#include "WatchCell.hpp"

namespace wrd {

    class Watcher : public Chunk {
        WRD_DECL_THIS(Watcher, Chunk)
        WRD_INIT_META(This)
        friend class Instancer;
        friend class BindTag;

    public:
        //  Watcher:
        Watcher();

        WatchCell& operator[](widx n);
        WatchCell& operator[](Id id);
        const WatchCell& operator[](widx n) const WRD_UNCONST_FUNC(operator[](n))
        const WatchCell& operator[](Id id) const WRD_UNCONST_FUNC(operator[](id))

        WatchCell& get(widx n);
        WatchCell& get(Id id);
        const WatchCell& get(widx n) const WRD_UNCONST_FUNC(get(n));
        const WatchCell& get(Id id) const WRD_UNCONST_FUNC(get(id));
        //  Allocator:
        void* new1();

    protected:
        //  Watcher:
        Id _genId(void* pt) const;
        widx _getIdx(void* it) const;
    };
}
