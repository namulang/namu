#pragma once

#include "chunk.hpp"

namespace namu {

    class _wout chunks : public allocator {
        WRD_DECL_ME(chunks, allocator)
        WRD_INIT_META(me)

    public:
        //  chunks:
        explicit chunks(wcnt blkbyte = 0);
        virtual ~chunks();

        chunk& operator[](widx n);
        const chunk& operator[](widx n) const WRD_UNCONST_FUNC(operator[](n))
        chunk& operator[](const instance& inst);
        const chunk& operator[](const instance& inst) const WRD_UNCONST_FUNC(operator[](inst))

        //  chunks:
        chunk& get(widx n);
        chunk& get(const instance& it);
        const chunk& get(widx n) const WRD_UNCONST_FUNC(get(n))
        const chunk& get(const instance& it) const WRD_UNCONST_FUNC(get(it))
        //  allocator:
        void* new1() override;
        wbool del(void* pt, wcnt sz) override;
        /// @remark @ref chunk can resize its data. but can't persist whole memory allocated before,
        ///         it's a kind of memory flashing and can't give a way for accessing it.
        ///         at outside, ptr for them should be daggled.
        virtual wbool resize(wcnt new1);
        //  MemoryHaver:
        wbool has(const instance& it) const override;
        wcnt len() const override;
        wcnt size() const override;
        wbool rel() override;

    private:
        //  chunks:
        widx _findCapable();
        wbool _rel();
        //  MemoryHaver:
        void* _get(widx n) override;

        std::vector<chunk*> _chunks;
        int _s;
    };
}
