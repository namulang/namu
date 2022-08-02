#pragma once

#include "chunks.hpp"

namespace namu {

    class _wout pool : public memoryHaver {
        WRD_DECL_ME(pool, memoryHaver)
        WRD_INIT_META(me)

    public:
        //  pool:
        pool();
        virtual ~pool();

        chunks& operator[](widx n);
        chunks& operator[](const instance& inst);
        const chunks& operator[](widx n) const WRD_UNCONST_FUNC(operator[](n))
        const chunks& operator[](const instance& inst) const WRD_UNCONST_FUNC(operator[](inst))


        chunks& get(const instance& inst);
        chunks& get(widx n);
        const chunks& get(const instance& inst) const WRD_UNCONST_FUNC(get(inst))
        const chunks& get(widx n) const WRD_UNCONST_FUNC(get(n))
        //  memoryHaver:
        wbool has(const instance& it) const override;
        wcnt size() const override;
        wcnt len() const override;
        wbool rel() override;

    protected:
        //  memoryHaver:
        void* _get(widx n) override;

    private:
        std::vector<chunks*> _chunks;
    };
}
