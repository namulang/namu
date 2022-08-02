#pragma once

#include "memoryHaver.hpp"

namespace namu {

    class _wout allocator : public memoryHaver {
        WRD_DECL_ME(allocator)
        WRD_INIT_META(me)

    public:
        //  allocator:
        explicit allocator(wcnt blksize = 1);

        virtual void* new1() = 0;
        virtual wbool del(void* used, wcnt sz) = 0;
        wcnt getBlkSize() const;

    private:
        wcnt _blksize;
    };
}
