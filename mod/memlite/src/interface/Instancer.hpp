#pragma once

#include "../pool/Pool.hpp"
#include "../watcher/Watcher.hpp"

namespace wrd {

    class Instancer {
        WRD_DECL_THIS(Instancer)
        WRD_INIT_META(This)
        friend class Instance;

    public:
        wbool bind(Instance& new1);
        wbool unbind(Instance& old);
        Pool& getPool();
        Watcher& getWatcher();
        static WRD_SINGLETON_GETTER(This)

    private:
        void* _new1(size_t sz);
        void _del(void* pt, wcnt sz);
        wbool _hasBindTag(Instance& it);

        Pool _pool;
        Watcher _watcher;
    };
}
