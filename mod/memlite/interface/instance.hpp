#pragma once

#include "id.hpp"
#include <map>

struct namuTest;

namespace namu {

    class bindTag;
    class instancer;

    class _wout instance : public typeProvidable {
        WRD_DECL_ME(instance)
        WRD_INIT_META(me)
        friend class bindTag;
        friend class watcher; // for vault.
        friend class chunks; // for vault.
        friend class instancer; // for _id.
        friend struct ::namuTest; // for vault.

    public:
        class vault {

        public:
            wbool set(void* rcver, widx chkN);
            widx get(void* rcver);
            wcnt len() const;
            wbool rel();
            std::map<void*, int>& getVaults();

        private:
            std::map<void*, int> _vaults;
        };

        //  instance:
        instance();
        explicit instance(id newId);
        instance(const me& rhs);
        virtual ~instance();

        void* operator new(size_t sz);
        void operator delete(void* pt, size_t sz);

        virtual id getId() const;
        virtual wbool isHeap() const;
        const bindTag& getBindTag() const;

    protected:
        //  instance:
        wbool _setId(id new1);
        static instancer& _getMgr();

    private:
        id _id;
        static vault _vault;
    };
}
