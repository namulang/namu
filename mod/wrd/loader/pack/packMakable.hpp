#pragma once

#include "../../builtin/res/tpair.hpp"

namespace wrd {

    class pack;
    class src;
    class errReport;
    class containable;
    template <typename T> class tnarr;
    typedef tnarr<src> srcs;

    class packMakable {
        WRD_DECL_ME(packMakable)
        WRD_INIT_META(me)

    public:
        virtual tstr<srcs> parse(errReport& rpt, containable& tray) = 0;
        virtual wbool verify(errReport& rpt, pack& pak) = 0;
    };
}
