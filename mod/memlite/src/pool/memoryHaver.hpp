#pragma once

#include "../common.hpp"

namespace wrd {

    class instance;
    class memoryHaver {
        WRD_DECL_ME(memoryHaver)
        WRD_INIT_META(me)

    public:
        virtual ~memoryHaver() {}

        virtual wbool has(const instance& it) const = 0;
        virtual wcnt getLen() const = 0;
        virtual wcnt getSize() const = 0;
        virtual wbool rel() = 0;
        wbool isFull() const;
        wbool isCapable() const;

    protected:
        virtual void* _get(widx n) = 0;
    };
}
