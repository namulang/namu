#pragma once

#include "Chunk.hpp"

namespace wrd {

    class Chunks : public Allocator {
        WRD_DECL_THIS(Chunks, Allocator)
        WRD_INIT_META(This)

    public:
        //  Chunks:
        Chunks(wcnt blkbyte = 0);
        virtual ~Chunks();

        Chunk& operator[](widx n);
        Chunk& operator[](Instance& inst);

        //  Chunks:
        Chunk& get(widx n);
        Chunk& get(Instance& it);
        //  Allocator:
        void* new1();
        wbool del(void* pt, wcnt sz);
        wbool resize(wcnt new1);
        //  MemoryHaver:
        wbool has(Instance& it);
        wcnt getLen();
        wcnt getSize();
        wbool rel();

    private:
        //  Chunks:
        widx _findCapable();
        wbool _rel();
        //  MemoryHaver:
        void* _onGet(widx n) override;

        std::vector<Chunk*> _chunks;
        int _s;
    };
}
