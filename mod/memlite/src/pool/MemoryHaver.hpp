#pragma once

#include "../common.hpp"

namespace wrd {

    class Instance;
    class MemoryHaver {
        WRD_DECL_THIS(MemoryHaver)
        WRD_INIT_META(This)

    public:
        virtual wbool has(Instance& it) = 0;
        virtual wcnt getLen() = 0;
        virtual wcnt getSize() = 0;
        virtual wbool rel() = 0;
        wbool isFull();
        wbool isCapable();

    protected:
        virtual void* _get(widx n) = 0;
    };
}
