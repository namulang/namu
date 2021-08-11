#pragma once

#include "../common.hpp"

namespace wrd {

    class pack;
    template <typename T> class tnchain;
    typedef tnchain<pack> packChain;

    class obj;
    template <typename T> class tnarr;
    typedef wrd::tnarr<wrd::obj> origins;

    class packMakable {
        WRD_DECL_ME(packMakable)
        WRD_INIT_META(me)

    public:
        virtual origins& make() = 0;
        virtual wbool verify(const packChain& mergedPacks) = 0;
        virtual wbool link(const packChain& mergedPacks) = 0;
    };
}
