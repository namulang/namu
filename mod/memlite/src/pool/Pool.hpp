#pragma once

#include "Chunks.hpp"

namespace wrd {

    class Pool : public MemoryHaver {
        WRD_DECL_THIS(Pool, MemoryHaver)
        WRD_INIT_META(This)

    public:
        //  Pool:
        Pool();
        virtual ~Pool();

        Chunks& operator[](widx n);
        Chunks& operator[](Instance& inst);

        Chunks& get(Instance& inst);
        Chunks& get(widx n);
        //  MemoryHaver:
        wbool has(Instance& it) override;
        wcnt getSize() override;
        wcnt getLen() override;
        wbool rel() override;

    protected:
        //  MemoryHaver:
        void* _get(widx n) override;

    private:
        std::vector<Chunks*> _chunks;
    };
}
