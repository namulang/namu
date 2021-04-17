#pragma once

#include "id.hpp"
#include <map>

struct chunksFixture;

namespace wrd {

    class bindTag;
    class instancer;

    class instance : public typeProvidable {
        WRD_DECL_ME(instance)
        WRD_INIT_META(me)
        friend class bindTag;
        friend class watcher; // for vault.
        friend class chunks; // for vault.
        friend class instancer; // for _id.
        friend struct ::chunksFixture; // for vault.

    public:
        class vault {

        public:
            wbool set(void* rcver, widx chkN);
            widx get(void* rcver);
            wbool rel();

            std::map<void*, int>& getVaults() {
                return _vaults;
            }

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
