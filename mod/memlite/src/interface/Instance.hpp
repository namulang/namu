#pragma once

#include "Id.hpp"
#include <map>

namespace wrd {

    class BindTag;
    class Instancer;

    class Instance : public TypeProvidable {
        WRD_DECL_THIS(Instance)
        WRD_INIT_META(This)
        friend class BindTag;
        friend class Watcher; // for Vault.
        friend class Chunks; // for Vault.
        friend class Instancer; // for _id.

    public:
        struct Defaulter {
            widx n = WRD_INDEX_ERROR;
        };

        class Vault {

        public:
            wbool set(void* rcver, widx chkN);
            widx get(void* rcver);
            wbool rel();

        private:
            std::map<void*, Defaulter> _vaults;
        };

        //  Instance:
        Instance();
        Instance(Id id);
        Instance(const This& rhs);
        virtual ~Instance();

        void* operator new(size_t sz);
        void operator delete(void* pt, size_t sz);

        virtual Id getId() const;
        virtual wbool isHeap() const;
        const BindTag& getBindTag() const;

    protected:
        //  Instance:
        wbool _setId(Id new1);
        static BindTag& _getBindTag(Id id);
        static Instancer& _getMgr();

    private:
        Id _id;
        static Vault _vault;
    };
}
