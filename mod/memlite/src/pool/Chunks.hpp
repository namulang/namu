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
        const Chunk& operator[](widx n) const WRD_UNCONST_FUNC(operator[](n))
        Chunk& operator[](const Instance& inst);
        const Chunk& operator[](const Instance& inst) const WRD_UNCONST_FUNC(operator[](inst))

        //  Chunks:
        Chunk& get(widx n);
        Chunk& get(const Instance& it);
        const Chunk& get(widx n) const WRD_UNCONST_FUNC(get(n))
        const Chunk& get(const Instance& it) const WRD_UNCONST_FUNC(get(it))
        //  Allocator:
        void* new1() override;
        wbool del(void* pt, wcnt sz) override;
        /// @remark @ref Chunk can resize its data. but can't persist whole memory allocated before,
        ///         it's a kind of memory flashing and can't give a way for accessing it.
        ///         at outside, ptr for them should be daggled.
        virtual wbool resize(wcnt new1);
        //  MemoryHaver:
        wbool has(const Instance& it) const override;
        wcnt getLen() const override;
        wcnt getSize() const override;
        wbool rel() override;

    private:
        //  Chunks:
        widx _findCapable();
        wbool _rel();
        //  MemoryHaver:
        void* _get(widx n) override;

        std::vector<Chunk*> _chunks;
        int _s;
    };
}
