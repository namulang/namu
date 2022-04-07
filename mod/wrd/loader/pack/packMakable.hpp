#pragma once

#include "../../builtin/res/tpair.hpp"

namespace wrd {

    class pack;
    class src;
    class errReport;
    template <typename K, typename V> class tbicontainable;
    typedef tbicontainable<std::string, node> bicontainable;
    template <typename T, typename WRP> class tnarr;
    typedef tnarr<src, strTactic> srcs;

    class packMakable {
        WRD_DECL_ME(packMakable)
        WRD_INIT_META(me)

    public:
        virtual tstr<srcs> parse(errReport& rpt, bicontainable& tray) = 0;
        virtual wbool verify(errReport& rpt, pack& pak) = 0;
    };
}
