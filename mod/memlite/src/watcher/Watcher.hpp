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

        WatchCell& get(widx n);
        WatchCell& get(Id id);
        //  Allocator:
        void* new1();

    protected:
        //  Watcher:
        Id _genId(void* pt);
        widx _getIdx(void* it);
    };
}
