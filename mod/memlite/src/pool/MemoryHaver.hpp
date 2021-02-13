#pragma once

#include "../common.hpp"

namespace wrd {

    class Instance;
    class MemoryHaver {
        WRD_DECL_THIS(MemoryHaver)
        WRD_INIT_META(This)

    public:
        virtual ~MemoryHaver() {}
        virtual wbool has(const Instance& it) const = 0;
        virtual wcnt getLen() const = 0;
        virtual wcnt getSize() const = 0;
        virtual wbool rel() = 0;
        wbool isFull() const;
        wbool isCapable() const;

    protected:
        virtual void* _get(widx n) = 0;
    };
}
