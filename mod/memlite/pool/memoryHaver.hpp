#pragma once

#include "../common.hpp"

namespace namu {

    class instance;
    class _nout memoryHaver {
        NAMU_DECL_ME(memoryHaver)
        NAMU_INIT_META(me)

    public:
        virtual ~memoryHaver() {}

        virtual nbool has(const instance& it) const = 0;
        virtual ncnt len() const = 0;
        virtual ncnt size() const = 0;
        virtual nbool rel() = 0;
        nbool isFull() const;
        nbool isCapable() const;

    protected:
        virtual void* _get(nidx n) = 0;
    };
}
