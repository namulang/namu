#pragma once

#include "Chunks.hpp"

namespace wrd {

    class Pool : public MemoryHaver {
        WRD_DECL_ME(Pool, MemoryHaver)
        WRD_INIT_META(me)

    public:
        //  Pool:
        Pool();
        virtual ~Pool();

        Chunks& operator[](widx n);
        Chunks& operator[](const Instance& inst);
        const Chunks& operator[](widx n) const WRD_UNCONST_FUNC(operator[](n))
        const Chunks& operator[](const Instance& inst) const WRD_UNCONST_FUNC(operator[](inst))


        Chunks& get(const Instance& inst);
        Chunks& get(widx n);
        const Chunks& get(const Instance& inst) const WRD_UNCONST_FUNC(get(inst))
        const Chunks& get(widx n) const WRD_UNCONST_FUNC(get(n))
        //  MemoryHaver:
        wbool has(const Instance& it) const override;
        wcnt getSize() const override;
        wcnt getLen() const override;
        wbool rel() override;

    protected:
        //  MemoryHaver:
        void* _get(widx n) override;

    private:
        std::vector<Chunks*> _chunks;
    };
}
