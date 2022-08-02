#pragma once

#include "../common.hpp"

namespace namu {

    class instance;
    class _wout memoryHaver {
        WRD_DECL_ME(memoryHaver)
        WRD_INIT_META(me)

    public:
        virtual ~memoryHaver() {}

        virtual wbool has(const instance& it) const = 0;
        virtual wcnt len() const = 0;
        virtual wcnt size() const = 0;
        virtual wbool rel() = 0;
        wbool isFull() const;
        wbool isCapable() const;

    protected:
        virtual void* _get(widx n) = 0;
    };
}
