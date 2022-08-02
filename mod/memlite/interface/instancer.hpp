#pragma once

#include "../pool/pool.hpp"
#include "../watcher/watcher.hpp"

namespace namu {

    class _wout instancer {
        WRD_DECL_ME(instancer)
        WRD_INIT_META(me)
        friend class instance;

    public:
        wbool bind(const instance& new1);
        wbool rel(const instance& old);
        const pool& getPool() const;
        const watcher& getWatcher() const;
        static WRD_SINGLETON_GETTER(me)

    private:
        void* _new1(size_t sz);
        void _del(void* pt, wcnt sz);
        wbool _hasBindTag(const instance& it) const;


    private:
        pool _pool;
        watcher _watcher;
    };
}
